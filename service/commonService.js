var self = {};

/**
 * 封装后的请求方法
 * url       请求路由
 * data      请求参数
 * method    请求方法
 * callback  成功后执行的回调函数
 */
self.request = function(url, data, method, callback) {
    wx.request({
        url: 'https://douban.uieee.com/v2/movie/' + url,
        data: data,
        method: method,
        header: {
            "Content-Type": "json"
        },
        success: function (response) {
            if (callback) {
                callback(response.data);
            }
        },
        fail: function (response) {
            console.log('请求失败');
        }
    });
};

module.exports.request = self.request;