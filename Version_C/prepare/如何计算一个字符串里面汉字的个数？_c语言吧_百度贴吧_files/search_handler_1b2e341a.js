_.Module.define({path:"common/component/search_handler",sub:{_staticUrl:{no_key:"http://tieba.baidu.com/","\u8d34\u5427\u6295\u8bc9":"http://tieba.baidu.com/tousu/new","\u5e16\u5427\u6295\u8bc9":"http://tieba.baidu.com/tousu/new",tiebatousu:"http://tieba.baidu.com/tousu/new","\u8d34\u5427\u6295\u8bc9\u5427":"http://tieba.baidu.com/tousu/new","\u8d34\u5427\u6295\u8bc9\u4e2d\u5fc3":"http://tieba.baidu.com/tousu/new","\u6295\u8bc9\u4e2d\u5fc3":"http://tieba.baidu.com/tousu/new","\u6295\u8bc9":"http://tieba.baidu.com/tousu/new","\u8d34\u5427\u4e3e\u62a5":"http://tieba.baidu.com/tousu/new","\u77e5\u9053\u6295\u8bc9":"http://tousu.baidu.com/zhidao","\u7a7a\u95f4\u6295\u8bc9":"http://tousu.baidu.com/hi","\u767e\u79d1\u6295\u8bc9":"http://tousu.baidu.com/baike",zhidaotousu:"http://tousu.baidu.com/zhidao",kongjiantousu:"http://tousu.baidu.com/hi",baiketousu:"http://tousu.baidu.com/baike"},_sendStatistics:function(b,a){$.stats.sendRequest("st_mod=search&search_type="+b)},initial:function(){},toStaticUrl:function(b){var a=b.toLowerCase();if(this._staticUrl.hasOwnProperty(a)){$.tb.location.setHref(this._staticUrl[a]);return false}},enterBa:function(a,b){if(a==""){$.tb.location.setHref(this._staticUrl.no_key);return false}this.toStaticUrl(a);var d=[];if(a.indexOf("\uff1a")!=-1){d=a.split("\uff1a")}else{d=a.split(":")}if(d.length==2){if(d[0]=="\u6807\u7b7e"){this._sendStatistics("tagsearch",a);$.tb.location.setHref("/f/search/fm?ie=utf-8&tag="+encodeURIComponent(d[1]));return false}else{if(d[0].indexOf("\u5427\u5185")!=-1){var c=d[0].split("\u5427\u5185")[0];if(c){this._sendStatistics("baneisearch",a);$.tb.location.setHref("/f/search/res?ie=utf-8&kw="+encodeURIComponent(c)+"&qw="+encodeURIComponent(d[1]));return false}}}}if(PageData.search_what&&b!="fromBtn"){if(PageData.search_what=="composite"){this._sendStatistics("compositesearch",a);$.tb.location.setHref("/f/search/res?ie=utf-8&qw="+encodeURIComponent(a));return false}else{if(PageData.search_what=="forum"){this._sendStatistics("forumsearch",a);$.tb.location.setHref("/f/search/fm?ie=utf-8&qw="+encodeURIComponent(a));return false}}}this._sendStatistics("enterba&from=search",a);$.tb.location.setHref("/f?ie=utf-8&kw="+encodeURIComponent(a));return false},searchPost:function(a){if(!window.history_search_post){if(PageData.user.is_login){$.tb.post("/f/search/addWord",{word:a},function(b){if(b.no==0){window.history_search_post=false}})}window.history_search_post=true}this._sendStatistics("postsearch",a);setTimeout(function(){$.tb.location.setHref("/f/search/res?ie=utf-8&qw="+encodeURIComponent(a))},100);return false},searchPostInBa:function(c,a){var b="/f/search/res?ie=utf-8&kw="+encodeURIComponent(a)+"&qw="+encodeURIComponent(c);if(!window.history_search_post){if(PageData.user.is_login){$.tb.post("/f/search/addWord",{word:c},function(d){if(d.no==0){window.history_search_post=false}})}window.history_search_post=true}this._sendStatistics("baneisearch",c);setTimeout(function(){$.tb.location.setHref(b)},100);return false},searchPeople:function(a){this._sendStatistics("peoplesearch",a);$.tb.location.setHref("/f/search/sure?ie=utf-8&only_user=1&qw="+encodeURIComponent(a));return false},searchTag:function(a){this._sendStatistics("tagsearch",a);$.tb.location.setHref("/f/search/fm?ie=utf-8&tag="+encodeURIComponent(a));return false},searchForum:function(b){var a="/f/search/fm?ie=UTF-8&";if(b.indexOf("\u6807\u7b7e\uff1a")!=-1){b=b.substr(b.indexOf("\u6807\u7b7e\uff1a")+3);a=a+"tag="+encodeURIComponent(b)}else{if(b.indexOf("\u6807\u7b7e:")!=-1){b=b.substr(b.indexOf("\u6807\u7b7e:")+3);a=a+"tag="+encodeURIComponent(b)}else{a=a+"qw="+encodeURIComponent(b)}}$.tb.location.setHref(a);return false}}});