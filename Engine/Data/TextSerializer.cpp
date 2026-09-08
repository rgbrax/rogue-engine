#include "Data/TextSerializer.h"
#include "Data/DefRegistry.h"

#include <charconv>
#include <cstdio>
#include <vector>

namespace rogue
{
	namespace
	{
		std::string_view Trim(std::string_view s)
		{
			while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\r'))
				s.remove_prefix(1);
			while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r'))
				s.remove_suffix(1);
			return s;
		}

		void SplitFirstToken(std::string_view line, std::string_view& outKey, std::string_view& outRest)
		{
			const size_t space = line.find_first_of(" \t");
			if (space == std::string_view::npos)
			{
				outKey = line;
				outRest = {};
				return;
			}

			outKey = line.substr(0, space);
			outRest = Trim(line.substr(space));
		}

		std::string FloatToText(double v)
		{
			char buffer[64];
			const auto result = std::to_chars(buffer, buffer + sizeof(buffer), v);
			return std::string(buffer, result.ptr);
		}

		//skip keeps the default field, error stops the field
		enum class ParseResult
		{
			Ok,
			Skip,
			Error
		};

		std::string_view EnumToName(const FieldDesc& field, int64_t value)
		{
			for (const EnumEntry& entry : field.enumValues)
			{
				if (entry.value == value)
					return entry.name;
			}

			return {};
		}

		bool NameToEnum(const FieldDesc& field, std::string_view name, int64_t& outValue)
		{
			for (const EnumEntry& entry : field.enumValues)
			{
				if (entry.name == name)
				{
					outValue = entry.value;
					return true;
				}
			}

			return false;
		}

		std::string ValueToText(const FieldDesc& field, const Value& v)
		{
			switch (field.type)
			{
			case FieldType::Bool:
				return std::get<bool>(v) ? "true" : "false";
			case FieldType::Int:
				return std::to_string(std::get<int64_t>(v));

			case FieldType::Enum: {
				const int64_t n = std::get<int64_t>(v);
				const std::string_view name = EnumToName(field, n);
				return name.empty() ? std::to_string(n) : std::string(name); //unnamed enum val will return number
			}
			case FieldType::Float:
				return FloatToText(std::get<double>(v));
			case FieldType::String:
				return "\"" + std::get<std::string>(v) + "\"";
			case FieldType::Ref:
				return std::to_string(std::get<DefId>(v).value);
			}

			return {};
		}

		ParseResult TextToValue(const FieldDesc& field, std::string_view text, Value& outValue)
		{
			switch (field.type)
			{
			case FieldType::Bool:
				outValue = (text == "true");
				return ParseResult::Ok;

			case FieldType::Int: {
				int64_t n = 0;
				const auto r = std::from_chars(text.data(), text.data() + text.size(), n);
				outValue = n;
				return r.ec == std::errc() ? ParseResult::Ok : ParseResult::Error;
			}

			case FieldType::Enum: {
				int64_t n = 0;
				if (NameToEnum(field, text, n))
				{
					outValue = n;
					return ParseResult::Ok;
				}

				//#tbd: remove once all enums are handled as text
				const auto r = std::from_chars(text.data(), text.data() + text.size(), n);
				if (r.ec == std::errc())
				{
					outValue = n;
					return ParseResult::Ok;
				}

				//log unknown names, maybe out of date
				std::printf("  warning: unknown value '%.*s' for enum field '%s', left at default\n",
							(int)text.size(), text.data(), field.name.c_str());
				return ParseResult::Skip;
			}

			case FieldType::Float: {
				double d = 0.0;
				const auto r = std::from_chars(text.data(), text.data() + text.size(), d);
				outValue = d;
				return r.ec == std::errc() ? ParseResult::Ok : ParseResult::Error;
			}

			case FieldType::String: {
				std::string_view s = text;
				if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
					s = s.substr(1, s.size() - 2);
				outValue = std::string(s);
				return ParseResult::Ok;
			}

			case FieldType::Ref: {
				uint64_t n = 0;
				const auto r = std::from_chars(text.data(), text.data() + text.size(), n);
				outValue = DefId{n};
				return r.ec == std::errc() ? ParseResult::Ok : ParseResult::Error;
			}
			}

			return ParseResult::Error;
		}
	}

	std::string TextSerializer::Write(const Def& def)
	{
		const Schema& schema = def.GetSchema();

		std::vector<const FieldDesc*> fields;
		schema.CollectFields(fields);

		std::string out;
		out += schema.TypeName();
		out += " ";
		out += def.editorId;
		out += "\n{\n";

		for (const FieldDesc* field : fields)
		{
			out += "\t";
			out += field->name;
			out += " ";
			out += ValueToText(*field, field->get(&def));
			out += "\n";
		}

		out += "}\n";
		return out;
	}

	std::string TextSerializer::WriteAll(const DefTable& table)
	{
		std::string out;
		for (const std::unique_ptr<Def>& def : table.All())
		{
			out += Write(*def);
			out += "\n";
		}

		return out;
	}

	bool TextSerializer::ReadAll(std::string_view text, DefTable& outTable, std::string* outError)
	{
		std::unique_ptr<Def> current;
		const Schema* schema = nullptr;
		size_t lineNumber = 0;

		while (!text.empty())
		{
			const size_t eol = text.find('\n');
			std::string_view line = Trim(eol == std::string_view::npos ? text : text.substr(0, eol));
			text = eol == std::string_view::npos ? std::string_view{} : text.substr(eol + 1);
			++lineNumber;

			if (line.empty() || line.front() == '#')
				continue;

			if (line == "{")
				continue;

			if (line == "}")
			{
				if (current != nullptr)
					outTable.Add(std::move(current));
				schema = nullptr;
				continue;
			}

			std::string_view key;
			std::string_view rest;
			SplitFirstToken(line, key, rest);

			if (current == nullptr) //no record open, assume we are in a header or def title
			{
				current = DefRegistry::Create(key);
				if (current == nullptr)
				{
					if (outError != nullptr)
						*outError = "line " + std::to_string(lineNumber) + ": unknown Def type '" + std::string(key) + "'";
					return false;
				}

				current->editorId = std::string(rest);
				schema = &current->GetSchema();
				continue;
			}

			const FieldDesc* field = schema->Find(key);

			//skip unrecognized fields, assume newer version
			if (field == nullptr)
			{
				std::printf("  warning line %zu: unknown field '%.*s', skipped\n",
							lineNumber, (int)key.size(), key.data());
				continue;
			}

			Value value;
			const ParseResult result = TextToValue(*field, rest, value);

			if (result == ParseResult::Skip)
				continue;

			if (result == ParseResult::Error)
			{
				if (outError != nullptr)
					*outError = "line " + std::to_string(lineNumber) + ": could not parse '" + std::string(rest) + "'";
				return false;
			}

			field->set(current.get(), value);
		}

		return true;
	}
}
