#include "Core/Schema.h"

namespace rogue
{
	Schema::Schema(std::string typeName, const Schema* parent)
		: m_typeName(std::move(typeName)), m_parent(parent)
	{
		return;
	}

	const std::string& Schema::TypeName() const
	{
		return m_typeName;
	}

	const Schema* Schema::Parent() const
	{
		return m_parent;
	}

	const std::vector<FieldDesc>& Schema::OwnFields() const
	{
		return m_fields;
	}

	void Schema::CollectFields(std::vector<const FieldDesc*>& out) const
	{
		if (m_parent != nullptr)
			m_parent->CollectFields(out);

		for (const FieldDesc& field : m_fields)
			out.push_back(&field);
	}

	const FieldDesc* Schema::Find(std::string_view name) const
	{
		for (const FieldDesc& field : m_fields)
		{
			if (field.name == name)
				return &field;
		}

		return m_parent != nullptr ? m_parent->Find(name) : nullptr;
	}

	void Schema::AddField(FieldDesc desc)
	{
		m_fields.push_back(std::move(desc));
	}
}
