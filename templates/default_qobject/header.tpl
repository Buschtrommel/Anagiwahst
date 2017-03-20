#ifndef {% if namespaces.size > 0 %}{{ namespaces|join|cut:","|upper}}{% endif %}{{ class|upper }}_H
#define {% if namespaces.size > 0 %}{{ namespaces|join|cut:","|upper}}{% endif %}{{ class|upper }}_H

#include <QObject>

{% if commentposition == 2 %}
/*!
 * \class {{ class }}
 * \brief The {{ class }} class.
 */
 
/*!
 * \fn {{ class }}::{{ class }}()
 * \brief Constructs a new {{ class }} object with default values and the given \a parent.
 */
 
/*!
 * \fn {{ class }}::~{{ class }}()
 * \brief Deconstructs the {{ class }} object.
 */

{% for prop in props %}


{% with 1 as showdesignator %}
{% include "propertycomment.tpl" %}
{% if prop.read and prop.documentMethods %}{% include "readcomment.tpl" %}{% endif %}
{% if prop.write and prop.documentMethods %}{% include "writecomment.tpl" %}{% endif %}
{% if prop.reset and prop.documentMethods %}{% include "resetcomment.tpl" %}{% endif %}
{% if prop.notify and prop.documentMethods %}{% include "notifycomment.tpl" %}{% endif %}
{% endwith %}
{% endfor %}

{% endif %}

{% for ns in namespaces %}
namespace {{ ns }} {
{% endfor %}

{% if commentposition == 1 %}
/*!
 * \brief The {{ class }} class.
 */
{% endif %}
class {{ class }}{% if parentclasses.size > 0 %} : {% for pc in parentclasses %}public {{ pc }}{% if not forloop.last %}, {% endif %}{% endfor %}{% endif %}
{
    Q_OBJECT
{% for prop in props %}
    {% if commentposition == 1 %}{% with 1 as indent %}{% include "propertycomment.tpl" %}{% endwith %}{% endif %}{% if commentposition == 1 %}    Q{% else %}Q{%endif %}_PROPERTY({{ prop.type }} {% if prop.pointer %}*{% endif %}{{ prop.name}}{% if prop.read %} READ {{ prop.read }}{% endif %}{% if prop.write %} WRITE {{ prop.write }}{% endif %}{% if prop.reset %} RESET {{ prop.reset }}{% endif %}{% if prop.notify %} NOTIFY {{ prop.notify }}{% endif %}{% if prop.revision > 0 %} REVISION {{ prop.revision}}{% endif %}{% if prop.designable %} DESIGNABLE {{ prop.designable }}{% endif %}{% if prop.scriptable %} SCRIPTABLE {{ prop.scriptable }}{% endif %}{% if not prop.stored %} STORED false{% endif %}{% if prop.user %} USER true{% endif %}{% if prop.constant %} CONSTANT{% endif %}{% if prop.final %} FINAL{% endif %})
{% endfor %}
public:
{% if commentposition == 1 %}
    /*!
     * \brief Constructs a new {{ class }} object with default values and the given \a parent.
     */
{% endif %}
    explicit {{ class }}(QObject *parent = nullptr);
{% if commentposition == 1 %}
    /*!
     * \brief Deconstructs the {{ class }} object.
     */
{% endif %}
    ~{{ class }}();
    
{% for prop in props %}
    {% if prop.read %}
    {% if commentposition == 1 and prop.documentMethods %}{% with 1 as indent %}{% include "readcomment.tpl" %}{% endwith %}    {% endif %}{{ prop.type }} {% if prop.pointer %}*{% endif %}{{ prop.read }}() const;
    {% endif %}
{% endfor %}

{% for prop in props %}
    {% if prop.write %}
    {% if commentposition == 1 and prop.documentMethods %}{% with 1 as indent %}{% include "writecomment.tpl" %}{% endwith %}    {% endif %}void {{ prop.write }}({% if prop.argsByRef %}const {% endif %}{{ prop.type }} {% if prop.argsByRef %}&{% elif prop.pointer %}*{% endif %}n{{ prop.name|capfirst }});
    {% endif %}
{% endfor %}

{% for prop in props %}
    {% if prop.reset %}
    {% if commentposition == 1 and prop.documentMethods %}{% with 1 as indent %}{% include "resetcomment.tpl" %}{% endwith %}    {% endif %}void {{ prop.reset }}();
    {% endif %}
{% endfor %}

Q_SIGNALS:
{% for prop in props %}
    {% if prop.notify %}
    {% if commentposition == 1 and prop.documentMethods %}{% with 1 as indent %}{% include "notifycomment.tpl" %}{% endwith %}    {% endif %}void {{ prop.notify }}({% if prop.argsByRef %}const {% endif %}{{ prop.type }} {% if prop.argsByRef %}&{% elif prop.pointer %}*{% endif %}{{ prop.name }});
    {% endif %}
{% endfor %}

private:
{% for prop in props %}
    {% if prop.stored %}{{ prop.type }} {% if prop.pointer %}*{% endif %}m_{{ prop.name }}{% if prop.defaultValue %} = {{ prop.defaultValue }}{% endif %};{% endif %}
{% endfor %}

    Q_DISABLE_COPY({{ class }})
};

{% for ns in namespaces %}
}
{% endfor %}

#endif // {% if namespaces.size > 0 %}{{ namespaces|join|cut:","|upper}}{% endif %}{{ class|upper }}_H
