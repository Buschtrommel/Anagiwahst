/*!
{% if showdesignator %}
{% if indent %}     *{% else %} *{% endif %} \fn void  {{ class }}::{{ prop.reset }}()
{% endif %}
{% if indent %}     *{% else %} *{% endif %} \brief Reset function for the \link {{ class }}::{{ prop.name }} {{ prop.name }} \endlink property.
{% if prop.read or prop.reset or prop.notify %}
{% if indent %}     *{% else %} *{% endif %} \sa {% if prop.read %}{{ class }}::{{ prop.read }}() {% endif %}{% if prop.write %}{{ class }}::{{ prop.write }}() {% endif %}{% if prop.notify %}{{ class }}::{{ prop.notify }}(){% endif %}
{% endif %}
{% if indent %}     *{% else %} *{% endif %}/
