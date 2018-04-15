// components/starGrade/starGrade.js
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
        star: 0,
        grade: ''
    },

    /**
     * 组件的方法列表
     */
    methods: {
        init: function() {
            var self = this;
            var star = Math.floor(self.data.stars / 10);
            var grade = '';
            if (self.data.score > 0) {
                grade = self.data.score;
            } else {
                grade = '暂无评分';
            }
            self.setData({
                star: star,
                grade: grade
            });
        }
    },

    attached: function () {
        this.init();
    }
})
