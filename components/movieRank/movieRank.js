var requestService = require('../../service/requestService.js');

Component({
    /**
     * 组件的属性列表
     */
    properties: {

    },

    /**
     * 组件的初始数据
     */
    data: {
        newMovies: []
    },

    ready: function() {
        var self = this;
        requestService.getNewMovies(function(data) {
            console.log(data.subjects);
            self.setData({
                newMovies: data.subjects
            });
        });
    },

    /**
     * 组件的方法列表
     */
    methods: {

    }
})
