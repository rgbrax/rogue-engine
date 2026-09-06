#pragma once
#include "Core/Ids.h"
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

namespace rogue
{
	enum class FieldType
	{
		Bool,
		Int,
		Float,
		String,
		Ref,
		Enum
	};

	using Value = std::variant<bool, int64_t, double, std::string, DefId>;
	template <typename>
	inline constexpr bool AlwaysFalse = false;

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
			static_assert(AlwaysFalse<M>, "Schema: unsupported field type");
	}

	struct FieldDesc
	{
		std::string name;
		FieldType type = FieldType::Int;
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

			m_schema.AddField(std::move(desc));
			return *this;
		}

		Schema Build()
		{
			return std::move(m_schema);
		}

	private:
		Schema m_schema;
	};
}
