{% comment %}
	Taken from https://digitaldrummerj.me/blogging-on-github-part-13-creating-an-article-series/
{% endcomment %}
{% if page.series %}

{% assign count = '0' %}
{% assign idx = '0' %}
{% for post in site.posts reversed %}
{% if post.series == page.series %}
{% capture count %}{{ count | plus: '1' }}{% endcapture %}
{% if post.url == page.url %}
{% capture idx %}{{count}}{% endcapture %}
{% endif %}
{% endif %}
{% endfor %}


<div class="panel seriesNote">
	<p><strong>{{ page.series }}:</strong> Part {{ idx }} of {{ count }}</p>
	<ul>
		{% assign count = '0' %}
		{% for post in site.posts reversed %}
		{% if post.series == page.series %}
		{% capture count %}{{ count | plus: '1' }}{% endcapture %}
		<li>Part {{ count }} -
			{% if page.url == post.url %}
			This Article
			{% else %}
			<a href="{{post.url}}">{{post.title}}</a>
			{% endif %}
		</li>
		{% endif %}
		{% endfor %}
	</ul>
</div>
{% endif %}