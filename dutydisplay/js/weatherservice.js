.pragma library

.import "ajax.js" as Ajax

function getWeather(success, failure) {
    Ajax.get("http://api.map.baidu.com/telematics/v3/weather?location=%E6%83%A0%E5%9F%8E&output=json&ak=EGgzZ22dsboWQEcPQ6KDQLknQd3YkkkP", success, failure);
}
