$(document).ready(function(){
	
	//1. you can change these URLs to point to the correct stream you create:
	
		//this url pulls the actual tweets (user data, tweet body, time, etc.)
		var url = "http://tweetriver.com/EdibleCircuits/test1.json";
		//this url pulls tweet meta-data (total # tweets per minute, day, etc.)
		var metaURL = "http://tweetriver.com/EdibleCircuits/test1/meta.json";
	
	
	//2. pull Mass Relevance json
	
	//2a. if you want to print out actual tweets, use this
		$.get(url, function(data) {
		
			//print entire JSON string to console (open console in the browser to see and parse accordingly)
			console.log(data);
		
			for(var i=0; i<data.length; i++){
			
				//grab stuff from JSON
				var userName = data[i].user.screen_name;
				var text = data[i].text;
				var time = data[i].created_at;
					var timeChunks = time.split(" ");
					var day = timeChunks[0];
					var month = timeChunks[1];
					var date = timeChunks[2];
					var minutes = timeChunks[3];
					var utc = timeChunks[4];
					var year = timeChunks[5];
			
				$("#tweets").append("<article class='tweet'><h3>" + userName + ":</h3><h4>" + text + "</h4><p>(" + minutes + " on " + day + ", " + month + " " + date + ")</p></article>")
			}
	
		},"JSONP");
	

	//2b. if you want just numbers & other data from META URL, use this
	
		$.get(metaURL, function(data) {
			
			//print entire JSON string to console (open console in the browser to see and parse accordingly)
			//console.log(data);
			var numTweets = data.count.approved;
			
			//print total number of tweets to #meta section
			$("#meta").html("<h2>total number of tweets = "+numTweets+"</h2>");
		
		},"JSONP");
	

});