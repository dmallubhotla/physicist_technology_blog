<div class="post-footer">
	<div class="post-metadata" title="Post categories">{{ page.tags | concat: page.categories | compact | join: ', '}}</div>
	<div title="Atom feed"><a href={{ "feed.xml" | relative_url }}>Subscribe with Atom</a></div>
</div>