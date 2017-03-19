#include "{{ class|lower }}.h"
{% if debugout %}#ifdef QT_DEBUG
#include <QtDebug>
#endif{% endif %}
{% for ns in namespaces %}
using namespace {{ ns }};
{% endfor %}

{% if commentposition == 0 %}
/*!
 * \class {{ class }}
 * \brief The {{ class }} class.
 */


/*!
 * \brief Constructs a new {{ class }} object with default values and the given \a parent.
 */
{% endif %}
{{ class }}::{{ class }}(QObject *parent){% if parentclasses.size > 0 %} : {% for pc in parentclasses %}{{ pc }}(parent){% if not forloop.last %}, {% endif %}{% endfor %}{% endif %}
{
}


{% if commentposition == 0 %}
/*!
 * \brief Deconstructs the {{ class }} object.
 */
{% endif %}
{{ class }}::~{{ class }}()
{
}


{% for prop in props %}

{% if commentposition == 0 %}
{% with 1 as showdesignator %}
{% include "propertycomment.tpl" %}
{% if prop.notify and prop.documentMethods %}{% include "notifycomment.tpl" %}{% endif %}
{% endwith %}
{% endif %}
{% if prop.read %}
{% if commentposition == 0 and prop.documentMethods %}{% include "readcomment.tpl" %}{% endif %}{{ prop.type }} {% if prop.pointer %}*{% endif %}{{ class }}::{{ prop.read }}() const; { return m_{{ prop.name }}; }
{% endif %}

{% if prop.write %}
{% if commentposition == 0 and prop.documentMethods %}{% include "writecomment.tpl" %}{% endif %}void {{ class }}::{{ prop.write }}({% if prop.argsByRef %}const {% endif %}{{ prop.type }} {% if prop.argsByRef %}&{% elif prop.pointer %}*{% endif %}{{ prop.name }})
{
{% if prop.notify %}
    if ({{ prop.name }} != m_{{ prop.name }}) {
        m_{{ prop.name }} = {{ prop.name }};
{% if debugout %}#ifdef QT_DEBUG
        qDebug() << "Changed {{ prop.name }} to" << m_{{ prop.name }};
#endif{% endif %}
        Q_EMIT {{ prop.notify }}({{ prop.read }}());
    }
{% else %}
    m_{{ prop.name }} = {{ prop.name }};
{% if debugout %}#ifdef QT_DEBUG
    qDebug() << "Set {{ prop.name }} to" << m_{{ prop.name }};
#endif{% endif %}
{% endif %}
}
{% endif %}

{% if prop.reset %}
{% if commentposition == 0 and prop.documentMethods %}{% include "resetcomment.tpl" %}{% endif %}void {{ class }}::{{ prop.reset }}()
{
{% if prop.notify %}
    if (m_{{ prop.name }} != {% if prop.defaultValue %}{{ prop.defaultValue }}{% else %}{{ prop.type }}(){% endif %}) {
        m_{{ prop.name }} = {% if prop.defaultValue %}{{ prop.defaultValue }}{% else %}{{ prop.type }}(){% endif %};
{% if debugout %}#ifdef QT_DEBUG
        qDebug() << "Reset {{ prop.name }} to" << m_{{ prop.name }};
#endif{% endif %}
        Q_EMIT {{ prop.notify }}({{ prop.read }}());
    }
{% else %}
    m_{{ prop.name }} = {% if prop.defaultValue %}{{ prop.defaultValue }}{% else %}{{ prop.type }}(){% endif %};
{% if debugout %}#ifdef QT_DEBUG
    qDebug() << "Reset {{ prop.name }} to" << m_{{ prop.name }};
#endif{% endif %}
{% endif %}
}
{% endif %}

{% endfor %}
