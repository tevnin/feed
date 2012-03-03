<?php
	$dir = 'renders';
	$filesArray=glob($dir."/*.jpg");
	$reverseArray= array_reverse($filesArray);    
	    for($i=0;$i<6;$i++) {
	        $line.="<img src='".$reverseArray[$i]."' class='individImg' width='320' height='240' />";
	         next($reverseArray);
	    }

		 echo $line;
?>
