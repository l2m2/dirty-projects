;(function(doc){
  // check_webp_feature:
  //   'feature' can be one of 'lossy', 'lossless', 'alpha' or 'animation'.
  //   'callback(feature, result)' will be passed back the detection result (in an asynchronous way!)
  function check_webp_feature(feature, callback) {
    var kTestImages = {
        lossy: "UklGRiIAAABXRUJQVlA4IBYAAAAwAQCdASoBAAEADsD+JaQAA3AAAAAA",
        lossless: "UklGRhoAAABXRUJQVlA4TA0AAAAvAAAAEAcQERGIiP4HAA==",
        alpha: "UklGRkoAAABXRUJQVlA4WAoAAAAQAAAAAAAAAAAAQUxQSAwAAAARBxAR/Q9ERP8DAABWUDggGAAAABQBAJ0BKgEAAQAAAP4AAA3AAP7mtQAAAA==",
        animation: "UklGRlIAAABXRUJQVlA4WAoAAAASAAAAAAAAAAAAQU5JTQYAAAD/////AABBTk1GJgAAAAAAAAAAAAAAAAAAAGQAAABWUDhMDQAAAC8AAAAQBxAREYiI/gcA"
    };
    var img = new Image();
    img.onload = function () {
        var result = (img.width > 0) && (img.height > 0);
        callback(feature, result);
    };
    img.onerror = function () {
        callback(feature, false);
    };
    img.src = "data:image/webp;base64," + kTestImages[feature];
  }

  check_webp_feature('lossy', function(feature, support){
    $('.webp').each(function(){
      if ($(this).is('img')) {
        var src = $(this).attr('data-src');
        if (support){
          src = src.replace(/\.jpg|\.png$/, '.webp');
        }
        $(this).attr('src', src);
      } else if ($(this).is('a')){
        var href = $(this).attr('data-href');
        if (support){
          href = href.replace(/\.jpg|\.png$/, '.webp');
        }
        $(this).attr('href', href);
      } else if ($(this).is('div')) {
        var data_bg =  $(this).attr('data-bg');
        if (support){
          data_bg = data_bg.replace(/\.jpg|\.png$/, '.webp');
        }
        $(this).attr('data-bg', data_bg);
      }
    });
  });
}(document));