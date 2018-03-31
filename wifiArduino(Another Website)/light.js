jQuery(function($) {
   $.urlParam = function(name){
        var results = new RegExp('[\?&]' + name + '=([^&#]*)').exec(window.location.href);
        if (results==null){
           return null;
        }
        else{
           return results[1] || 0;
        }
    }
    if($.urlParam('light') == 'on'){
           $('#light_img_on').show();
           $('#light_img_off').hide();
    }
    else{
     $('#light_img_off').show();
     $('#light_img_on').hide();
    }
});
