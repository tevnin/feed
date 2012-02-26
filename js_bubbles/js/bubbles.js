$(document).ready(function(){
	var url = "http://tweetriver.com/EdibleCircuits/test1.json";
	var metaURL = "http://tweetriver.com/EdibleCircuits/test1/meta.json";
	var numTweets;

	var canvas = document.getElementById("canv").getContext("2d");
	
	//pull Mass Relevance json and get #s
	$.get(metaURL, function(data) {
		console.log(data.count.approved);
		console.log(data);
		numTweets = data.count.approved;
		
	},"JSONP");
	
	
	//on click, draw particles
	$("#canv").click(function(){
		drawBalls(numTweets);

	});

	//set up particle class (from Nidhi's oF code)
	function Particle(){
		var posX,posY,velX,velY,frcX,frcY;
		var damping = 0.01;
		
		this.resetForce = function(){
			frcX = 0;
			frcY = 0;
		}
		
		this.addForce = function(x,y){
			frcX = frcX + x;
			frcY = frcY + y;
		}
		this.addDampingForce = function(){
			frcX = frcX - velX * damping;
			frcY = frcY - velY * damping;
		}
		this.setInitialCondition = function(px,py,vx,vy){
			posX = px;
			posY = py;
			velX = vx;
			velY = vy;
		}
		this.update = function(){
			velX = velX + frcX;
			velY = velY + frcY;
			posX = posX + velX;
			posY = posY + velY;
		}
		this.draw = function(){
			canvas.beginPath();
			canvas.arc(posX, posY, 3, 0, Math.PI * 2, false);
			canvas.closePath();
			canvas.strokeStyle = "#000";
			canvas.stroke();
			canvas.fillStyle = "#000";
			canvas.fill();
		}
		this.bounceOffWalls = function(){
			// sometimes it makes sense to damped, when we hit... for now, we don't
			var bDampedOnCollision = false;
			var bDidICollide = false;
			
			// what are the walls
				var minX = 0;
				var minY = 0;
				var maxX = $("#canv").width;
				var maxY = $("#canv").height;

				if (posX > maxX){
					posX = maxX; // move to the edge, (important!)
					velX *= -1;
					bDidICollide = true;
				} else if (posX < minX){
					posX = minX; // move to the edge, (important!)
					velX *= -1;
					bDidICollide = true;
				}

				if (posY > maxY){
					posY = maxY; // move to the edge, (important!)
					velY *= -1;
					bDidICollide = true;
				} else if (posY < minY){
					posY = minY; // move to the edge, (important!)
					velY *= -1;
					bDidICollide = true;
				}

				if (bDidICollide == true && bDampedOnCollision == true){
					velX *= 0.9;
					velY *=0.9;
				}
			
		}
	}
	
	//var particles = [];
	
	//draw particles based on # of tweets
	function drawBalls(number){
		
		for(var i=0;i<number/100;i++){
			var ball = new Particle();
			ball.setInitialCondition(Math.random()*1000,Math.random()*500,Math.random()*10, Math.random()*10);
			
			//how do i get this to loop?
			ball.resetForce();
			ball.addForce(0.0, 0.28);
			ball.addDampingForce();
			ball.bounceOffWalls();
			ball.update();
			ball.draw();
			
		}
	}
});