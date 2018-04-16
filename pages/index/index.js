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
        movieList: [],
        loading: true
    },

    onShow: function() {
        var self = this;
        self.getFilmList(self.data.tabs.selectedId, function(data) {
            self.setData({
                movieList: data.subjects,
                loading: false
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

        self.setData({
            movieList: [],
            loading: true
        });

        var componentId = e.componentId;
        var selectedId = e.selectedId;

        self.setData({
            [`${componentId}.selectedId`]: selectedId
        });

        self.getFilmList(selectedId, function(data) {
            self.setData({
                movieList: data.subjects,
                loading: false
            });
        });
    }
}));