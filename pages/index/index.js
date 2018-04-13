const { extend, Tab } = require('../../zanui/index');

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

    handleZanTabChange(e) {
        var componentId = e.componentId;
        var selectedId = e.selectedId;

        this.setData({
            [`${componentId}.selectedId`]: selectedId
        });
    }
}));