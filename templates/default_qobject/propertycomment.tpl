/*!
{% if showdesignator %}
{% if indent %}     *{% else %} *{% endif %} \property {{ class }}::{{ prop.name }}
{% endif %}
{% if prop.brief %}
{% if indent %}     *{% else %} *{% endif %} \brief {{ prop.brief|safe }}
{% endif %}
{% if prop.commentParts.size > 0 %}
{% if indent %}     *{% else %} *{% endif %} 
{% for commentPart in prop.commentParts %}
{% if indent %}     *{% else %} *{% endif %} {{ commentPart|safe }}
{% endfor %}
{% endif %}
{% if prop.documentMethods %}
{% if indent %}     *{% else %} *{% endif %}
{% if indent %}     *{% else %} *{% endif %} \par Access functions:
{% if prop.read %}
{% if indent %}     *{% else %} *{% endif %} \li {{ prop.type }} {% if prop.pointer %}*{% endif %}{{ prop.read }}() const
{% endif %}
{% if prop.write %}
{% if indent %}     *{% else %} *{% endif %} \li void {{ prop.write }}({% if prop.argsByRef %}const {% endif %}{{ prop.type }} {%if prop.argsByRef %}&{% endif %}{% if prop.pointer %}*{% endif %}n{{ prop.name|capfirst }})
{% endif %}
{% if prop.reset %}
{% if indent %}     *{% else %} *{% endif %} \li void {{ prop.reset }}()
{% endif %}
{% endif %}
{% if prop.notify and prop.documentMethods %}
{% if indent %}     *{% else %} *{% endif %}
{% if indent %}     *{% else %} *{% endif %} \par Notifier signal:
{% if indent %}     *{% else %} *{% endif %} \li void {{ prop.notify }}({% if prop.argsByRef %}const {% endif %}{{ prop.type }} {%if prop.argsByRef %}&{% endif %}{% if prop.pointer %}*{% endif %}{{ prop.name }})
{% endif %}
{% if indent %}     *{% else %} *{% endif %}/
