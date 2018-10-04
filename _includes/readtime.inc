{% comment %}
	taken from https://carlosbecker.com/posts/jekyll-reading-time-without-plugins/
{% endcomment %}
{% if page.usereadtime %}
<span class="reading-time" title="Estimated read time">
	{% assign words = content | number_of_words %}
	Estimated time to read:
	{% if words < 360 %}
		1 min
	{% else %}
		{{ words | divided_by:180 }} min
	{% endif %}
</span>
{% endif %}
