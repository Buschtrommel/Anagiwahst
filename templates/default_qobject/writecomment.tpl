/*!
{% if showdesignator %}
{% if indent %}     *{% else %} *{% endif %} \fn void  {{ class }}::{{ prop.write }}({% if prop.argsByRef %}const {% endif %}{{ prop.type }} {%if prop.argsByRef %}&{% endif %}{% if prop.pointer %}*{% endif %}{{ prop.name }})
{% endif %}
{% if indent %}     *{% else %} *{% endif %} \brief Setter function for the \link {{ class }}::{{ prop.name }} {{ prop.name }} \endlink property.
{% if prop.read or prop.reset or prop.notify %}
{% if indent %}     *{% else %} *{% endif %} \sa {% if prop.read %}{{ class }}::{{ prop.read }}() {% endif %}{% if prop.reset %}{{ class }}::{{ prop.reset }}() {% endif %}{% if prop.notify %}{{ class }}::{{ prop.notify }}(){% endif %}
{% endif %}
{% if indent %}     *{% else %} *{% endif %}/
