/*!
{% if showdesignator %}
{% if indent %}     *{% else %} *{% endif %} \fn void  {{ class }}::{{ prop.notify }}({% if prop.argsByRef %}const {% endif %}{{ prop.type }} {%if prop.argsByRef %}&{% endif %}{% if prop.pointer %}*{% endif %}{{ prop.name }})
{% endif %}
{% if indent %}     *{% else %} *{% endif %} \brief Notifier function for the \link {{ class }}::{{ prop.name }} {{ prop.name }} \endlink property.
{% if prop.read or prop.reset or prop.write %}
{% if indent %}     *{% else %} *{% endif %} \sa {% if prop.read %}{{ class }}::{{ prop.read }}() {% endif %}{% if prop.write %}{{ class }}::{{ prop.write }}(){% endif %} {% endif %}{% if prop.reset %}{{ class }}::{{ prop.reset }}()
{% endif %}
{% if indent %}     *{% else %} *{% endif %}/
