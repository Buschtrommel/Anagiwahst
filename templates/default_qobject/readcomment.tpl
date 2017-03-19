/*!
{% if showdesignator %}
{% if indent %}     *{% else %} *{% endif %} \fn {{ prop.type }} {% if prop.pointer %}*{% endif %}{{ class }}::{{ prop.read }}() const
{% endif %}
{% if indent %}     *{% else %} *{% endif %} \brief Getter function for the \link {{ class }}::{{ prop.name }} {{ prop.name }} \endlink property.
{% if prop.write or prop.reset or prop.notify %}
{% if indent %}     *{% else %} *{% endif %} \sa {% if prop.write %}{{ class }}::{{ prop.write }}() {% endif %}{% if prop.reset %}{{ class }}::{{ prop.reset }}() {% endif %}{% if prop.notify %}{{ class }}::{{ prop.notify }}(){% endif %}
{% endif %}
{% if indent %}     *{% else %} *{% endif %}/
