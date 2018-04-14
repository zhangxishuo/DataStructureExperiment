// components/star/star.js
Component({
    /**
     * 组件的属性列表
     */
    properties: {
        stars: {
            type: Number,
            value: 0
        },
        score: {
            type: Number,
            value: 0
        }
    },

    /**
     * 组件的初始数据
     */
    data: {
        blackStars: [],
        whiteStars: [],
        grade: ''
    },

    /**
     * 组件的方法列表
     */
    methods: {
        init: function () {
            var self = this;
            var star = Math.floor(self.data.stars / 10);
            var arrayBlack = [];
            var arrayWhite = [];
            var gradeInfo = '';
            for (let i = 0; i < star; i++) {
                arrayBlack.push(i);
            }
            for (let i = 0; i < 5 - star; i++) {
                arrayWhite.push(i);
            }
            if (self.data.score > 0) {
                gradeInfo = self.data.score;
            } else {
                gradeInfo = '暂无评分';
            }
            self.setData({
                blackStars: arrayBlack,
                whiteStars: arrayWhite,
                grade: gradeInfo
            });
        }
    },

    attached: function() {
        this.init();
    }
})
