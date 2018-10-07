{% if jekyll.environment == 'production' %}

<script>
	var dnt = navigator.doNotTrack || window.doNotTrack || navigator.msDoNotTrack;
	console.debug("Do not track: " + dnt);
	if (dnt != "1" && dnt != "yes") {
		var ga = document.createElement('script');
		ga.type = 'text/javascript';
		ga.async = true;
		ga.src = 'https://www.googletagmanager.com/gtag/js?id=UA-42866662-2';
		var s = document.getElementsByTagName('script')[0];
		s.parentNode.insertBefore(ga, s);

		window.dataLayer = window.dataLayer || [];
		function gtag() {
			dataLayer.push(arguments);
		}
		gtag('js', new Date());
		gtag('config', 'UA-42866662-2', { 'anonymize_ip': true });
	} else {
		console.debug("Do not track respected. Not loading Google Analytics");
	}
</script>

{% endif %}
