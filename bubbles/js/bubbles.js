$(document).ready(function(){
	var url = "http://tweetriver.com/EdibleCircuits/test1.json";
	var metaURL = "http://tweetriver.com/EdibleCircuits/test1/meta.json";
	
	var canvas = document.getElementById("canv").getContext("2d");
	
	$.get(metaURL, function(data) {
		console.log(data.count.approved);
		console.log(data);
		
		drawBalls(data.count.approved);
	},"JSONP");
	
	function drawBalls(number){
		
		for(var i=0;i<number;i++){
			canvas.beginPath();
			canvas.arc(i, Math.random()*500+moveY, 10, 0, Math.PI * 2, false);
			canvas.closePath();
			canvas.strokeStyle = "#000";
			canvas.stroke();
			canvas.fillStyle = "#000";
			canvas.fill();
			
		}

		
	}
});