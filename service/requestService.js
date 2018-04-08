var commonService = require('commonService.js');

var self = {};

/**
 * 获取某地区正在热映的电影
 * city      当前地区
 * callback  成功后执行的回调函数
 */
self.getWellReceivedMovies = function(city, callback) {
    var data = {
        city: city
    };
    commonService.request('in_theaters', data, 'GET', callback);
};

/**
 * 获取即将上映的电影列表
 * callback  成功后执行的回调函数
 */
self.getComingSoonMovies = function(callback) {
    commonService.request('coming_soon', {}, 'GET', callback);
};

/**
 * 获取新片榜
 * callback  成功后执行的回调函数
 */
self.getNewMovies = function(callback) {
    commonService.request('new_movies', {}, 'GET', callback);
};

module.exports.getWellReceivedMovies = self.getWellReceivedMovies;
module.exports.getComingSoonMovies = self.getComingSoonMovies;
module.exports.getNewMovies = self.getNewMovies;