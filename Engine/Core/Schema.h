#pragma once
#include "Core/Ids.h"
#include <cstdint>
#include <functional>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

namespace rogue
{
	enum class FieldType
	{
		None,
		Bool,
		Int,
		Float,
		String,
		Ref,
		Enum
	};

	using Value = std::variant<bool, int64_t, double, std::string, DefId>;

	template <typename M>
	constexpr FieldType FieldTypeOf()
	{
		if constexpr (std::is_same_v<M, bool>)
			return FieldType::Bool;
		else if constexpr (std::is_enum_v<M>)
			return FieldType::Enum;
		else if constexpr (std::is_integral_v<M>)
			return FieldType::Int;
		else if constexpr (std::is_floating_point_v<M>)
			return FieldType::Float;
		else if constexpr (std::is_same_v<M, std::string>)
			return FieldType::String;
		else if constexpr (std::is_same_v<M, DefId>)
			return FieldType::Ref;
		else
			return FieldType::None;
	}

	//name and value pairs for enum fields
	struct EnumEntry
	{
		std::string_view name;
		int64_t value = 0;

		constexpr EnumEntry(std::string_view entryName, int64_t entryValue)
			: name(entryName), value(entryValue)
		{
		}

		template <typename E>
			requires std::is_enum_v<E>
		constexpr EnumEntry(std::string_view entryName, E entryValue)
			: name(entryName), value(static_cast<int64_t>(entryValue))
		{
		}
	};

	struct FieldDesc
	{
		std::string name;
		FieldType type = FieldType::Int;
		std::span<const EnumEntry> enumValues;
		std::function<Value(const void*)> get;
		std::function<void(void*, const Value&)> set;
	};

	//list of fields that a 'type' has; i.e. promise / manifest per type
	class Schema
	{
	public:
		Schema() = default;
		Schema(std::string typeName, const Schema* parent);
		const std::string& TypeName() const;
		const Schema* Parent() const;
		const std::vector<FieldDesc>& OwnFields() const;
		void CollectFields(std::vector<const FieldDesc*>& out) const;
		const FieldDesc* Find(std::string_view name) const;
		void AddField(FieldDesc desc);

	private:
		std::string m_typeName;
		const Schema* m_parent = nullptr;
		std::vector<FieldDesc> m_fields;
	};

	template <typename T>
	class SchemaBuilder
	{
	public:
		explicit SchemaBuilder(std::string typeName, const Schema* parent = nullptr)
			: m_schema(std::move(typeName), parent)
		{
		}

		template <typename M>
		SchemaBuilder& Field(const char* name, M T::* member)
		{
			m_schema.AddField(MakeField(name, member));
			return *this;
		}

		template <typename M, size_t N>
		SchemaBuilder& EnumField(const char* name, M T::* member, const EnumEntry (&names)[N])
		{
			FieldDesc desc = MakeField(name, member);
			desc.enumValues = std::span<const EnumEntry>(names, N);
			m_schema.AddField(std::move(desc));
			return *this;
		}

		Schema Build()
		{
			return std::move(m_schema);
		}

	private:
		template <typename M>
		FieldDesc MakeField(const char* name, M T::* member)
		{
			FieldDesc desc;
			desc.name = name;
			desc.type = FieldTypeOf<M>();

			desc.get = [member](const void* obj) -> Value {
				const M& v = static_cast<const T*>(obj)->*member;
				if constexpr (std::is_same_v<M, bool>)
					return v;
				else if constexpr (std::is_enum_v<M>)
					return static_cast<int64_t>(v);
				else if constexpr (std::is_integral_v<M>)
					return static_cast<int64_t>(v);
				else if constexpr (std::is_floating_point_v<M>)
					return static_cast<double>(v);
				else
					return v;
			};

			desc.set = [member](void* obj, const Value& in) {
				M& v = static_cast<T*>(obj)->*member;
				if constexpr (std::is_same_v<M, bool>)
					v = std::get<bool>(in);
				else if constexpr (std::is_enum_v<M>)
					v = static_cast<M>(std::get<int64_t>(in));
				else if constexpr (std::is_integral_v<M>)
					v = static_cast<M>(std::get<int64_t>(in));
				else if constexpr (std::is_floating_point_v<M>)
					v = static_cast<M>(std::get<double>(in));
				else
					v = std::get<M>(in);
			};

			return desc;
		}

		Schema m_schema;
	};
}
