// components/star/star.js
Component({
    /**
     * 组件的属性列表
     */
    properties: {
        star: {
            type: Number,
            value: 0
        }
    },

    /**
     * 组件的初始数据
     */
    data: {
        blackStars: [],
        whiteStars: []
    },

    /**
     * 组件的方法列表
     */
    methods: {
        init: function () {
            var self = this;
            var star = self.data.star;
            var arrayBlack = [];
            var arrayWhite = [];
            for (let i = 0; i < star; i++) {
                arrayBlack.push(i);
            }
            for (let i = 0; i < 5 - star; i++) {
                arrayWhite.push(i);
            }
            self.setData({
                blackStars: arrayBlack,
                whiteStars: arrayWhite
            });
        }
    },

    attached: function() {
        this.init();
    }
})
