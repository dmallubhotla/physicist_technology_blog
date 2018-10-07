<head>
	<link href="http://gmpg.org/xfn/11" rel="profile">
	<script src='https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML' async></script>
	<meta http-equiv="content-type" content="text/html; charset=utf-8">

	<!-- Enable responsiveness on mobile devices-->
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1">
	{% include analytics.inc %}
	<title>
		{% if page.title %}
		{{ page.title }} &middot; {{ site.title }}
		{% else %}
		{{ site.title }} &middot; {{ site.tagline }}
		{% endif %}
	</title>

	<!-- CSS -->
	<link rel="stylesheet" href={{ "/public/css/poole.css" | relative_url }}>
	<link rel="stylesheet" href={{ "/public/css/syntax.css" | relative_url }}>
	<link rel="stylesheet" href={{ "/public/css/lanyon.css" | relative_url }}>
	<link rel="stylesheet" href={{ "/public/css/panel.css" | relative_url }}>
	<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=PT+Serif:400,400italic,700|PT+Sans:400">

	<!-- Icons -->
	<link rel="shortcut icon" href={{ "/public/favicon.ico" | relative_url }}>

</head>
