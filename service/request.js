var self = {};

self.baseRequest = function(url, callback) {
    wx.request({
        url: 'https://douban.uieee.com/v2/movie/' + url,
        data: '',
        header: {
            "Content-Type": "json"
        },
        method: 'GET',
        dataType: 'json',
        responseType: 'text',
        success: function (response) {
            if (callback) {
                callback(response.data);
            }
        },
        fail: function (response) {
            console.log(response);
        },
        complete: function (response) {},
    });
};

self.getInFilmList = function (callback) {
    self.baseRequest('in_theaters', callback);
};

self.getInComeList = function (callback) {
    self.baseRequest('coming_soon', callback);
};

module.exports.getInFilmList = self.getInFilmList;
module.exports.getInComeList = self.getInComeList;