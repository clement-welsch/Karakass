#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& _vb, const VertexBufferLayout& layout)
{
	Bind();
	_vb.Bind();
	const std::vector<VertexBufferElement>& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		auto& element = elements[i];

		GLCall(glEnableVertexAttribArray(i));

		GLCall(glVertexAttribPointer(
			i,
			element.m_count,
			element.m_type,
			element.m_normalized,
			layout.GetStride(),
			(const void*)offset
		));

		/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));*/

		offset += element.m_count * VertexBufferElement::GetSizeOfType(element.m_type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
