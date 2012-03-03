<!doctype html>
<!--[if lt IE 7]> <html class="no-js ie6 oldie" lang="en"> <![endif]-->
<!--[if IE 7]>    <html class="no-js ie7 oldie" lang="en"> <![endif]-->
<!--[if IE 8]>    <html class="no-js ie8 oldie" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="en"> <!--<![endif]-->
<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">

  <title>surface</title>
  <meta name="description" content="SURFACE is an interactive installation that reduces the immense scale of Beijing into an intimate and individual experience. Each person has an influence on their urban environment, and the greater city impacts each individual in turn. SURFACE reflects that experience by transforming a map of Beijing, enormous in scale, onto each individual's face, creating a digital mask that combines person and urban environment. Each unique hybrid mask is added into a series of remapped personal environments, which come together to represent the wealth of individual perspectives that create the spirit of Beijing.">
  <meta name="author" content="lara warman">

  <meta name="viewport" content="width=device-width,initial-scale=1">

  <!-- CSS concatenated and minified via ant build script-->
  <link rel="stylesheet" href="css/styleDisplay.css">
  <!-- end CSS-->

  <script type="text/javascript" src="js/libs/modernizr-2.0.6.min.js"></script>
  <script type="text/javascript" src="js/libs/jquery-1.6.2.min.js"></script>
	<!--[if lt IE 9]>
	<script src="js/html5.js" type="text/javascript"></script>
	<![endif]-->
<script>
   $(document).ready(function() {

var handle = setInterval(function () {
    $('section#rendersDisplay').load('rendersDisplay.php?doc=');
}, 3000);

});
</script>	
</head>

<body>
		
  <div id="container">
    <div id="mainDisplay" role="main">		
		<section id="rendersDisplay">
			
		</section>
		<section id="more">
			<a href="moreRenders.php">more images ></a>
		</section>

    </div>
    <footer>

    </footer>
  </div> <!--! end of #container -->


  <!-- scripts concatenated and minified via ant build script-->
  <script defer src="js/plugins.js"></script>
  <script defer src="js/script.js"></script>
  <!-- end scripts-->


<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-25922830-1']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

  <!--[if lt IE 7 ]>
    <script src="//ajax.googleapis.com/ajax/libs/chrome-frame/1.0.3/CFInstall.min.js"></script>
    <script>window.attachEvent('onload',function(){CFInstall.check({mode:'overlay'})})</script>
  <![endif]-->
  
</body>
</html>
