/*
(function($) {
    $.fn.poll = function(options){
       var $this = $(this);
       // extend our default options with those provided
       var opts = $.extend({}, $.fn.poll.defaults, options);
       setInterval(update, opts.interval);
 
       // method used to update element html
       function update(){
           $.ajax({
               type: opts.type,
               url: opts.url,
               success: opts.success
           });
       };
    };
 
    // default options
    $.fn.poll.defaults = {
       type: "POST",
       url: ".",
       success: '',
       interval: 2000
    };
})(jQuery);
*/