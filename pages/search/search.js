const { Field, extend } = require('../../zanui/index');
const request = require('../../service/request.js');

Page(extend({}, Field, {

    /**
     * 页面的初始数据
     */
    data: {
        param: '',
        movieList: []
    },

    /**
     * 生命周期函数--监听页面加载
     */
    onLoad: function (options) {

    },

    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady: function () {

    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow: function () {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide: function () {

    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload: function () {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh: function () {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom: function () {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage: function () {

    },

    search: function() {
        var self = this;
        request.searchFilm(self.data.param, function(data) {
            self.setData({
                movieList: data.subjects
            });
            console.log(self.data.movieList);
        });
    },

    // 输入框内容更改时触发
    handleZanFieldChange({ componentId, detail }) {
        this.setData({
            param: detail.value
        });
    }
}))