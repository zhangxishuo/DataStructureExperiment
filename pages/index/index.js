const { extend, Tab } = require('../../zanui/index');
const request = require('../../service/request.js');

Page(extend({}, Tab, {
    data: {
        tabs: {
            list: [{
                id: 'inFilm',
                title: '正在热映'
            }, {
                id: 'inCome',
                title: '即将上映'
            }],
            selectedId: 'inFilm'
        },
        movieList: []
    },

    onShow: function() {
        var self = this;
        self.getFilmList(self.data.tabs.selectedId, function(data) {
            console.log(data.subjects);
            self.setData({
                movieList: data.subjects
            });
        });
    },

    getFilmList (selectedId, callback) {
        if (selectedId === 'inFilm') {
            request.getInFilmList(callback);
        } else if (selectedId === 'inCome') {
            request.getInComeList(callback);
        }
    },

    handleZanTabChange (e) {
        var self = this;

        var componentId = e.componentId;
        var selectedId = e.selectedId;

        self.setData({
            [`${componentId}.selectedId`]: selectedId
        });

        self.getFilmList(selectedId, function(data) {
            self.setData({
                movieList: data.subjects
            });
        });
    }
}));