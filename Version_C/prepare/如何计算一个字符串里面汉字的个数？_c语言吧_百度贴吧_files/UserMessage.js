var initItiebaMessage;new (function(){TbICom.call(this);var a="";var J=[];var d;var e;var O;var ab;var s;var j={atme:0,light:0,reply:0,favts:0,recycle:0};var B="default";var R=false;var G={all_msg:{id:0,display:true,aside_tip_id:"",url:""},fans:{id:1,url:"#itb_home#&type=fans",aside_tip_id:"",display:true},evaluate:{id:2,url:"#itb_home#&type=my_evaluate",aside_tip_id:"new_evaluate_num_tip",display:true},wealth:{id:3,url:"",display:true},reply:{id:4,url:"#itb_home#&type=replyme",aside_tip_id:"new_reply_num_tip",display:true},feature:{id:5,url:"#itb_home#&type=feature",aside_tip_id:"new_feature_num_tip",display:true},guess:{id:6,url:"#itb_home#&type=main",aside_tip_id:"new_guess_num_tip",display:true},postPasser:{id:8,display:false},atme:{id:9,url:"#itb_home#&type=atme",aside_tip_id:"new_atme_num_tip",display:true},recycle:{id:10,url:"/pmc/recycle",aside_tip_id:"new_recycle_num_tip",display:true},invite:{id:11,url:"#itb_home#",aside_tip_id:"new_invite_num_tip",display:true},light:{id:12,url:"#itb_home#&type=light",aside_tip_id:"new_light_num_tip",display:true},paperprops:{id:16,url:"http://tieba.baidu.com/tb/zt/tietiao/index.html",aside_tip_id:"new_paperprops_num_tip",display:true},newask:{id:17,url:"#itb_home#",aside_tip_id:"new_newask_num_tip",display:true},newcard:{id:18,url:"#itb_home#",aside_tip_id:"new_newcard_num_tip",display:true},favts:{id:20,url:"#itb_home#&type=storethread",aside_tip_id:"new_storethread_num_tip",display:true},clientnews:{id:21,url:"http://c.tieba.baidu.com/c/s/download/pc?src=webtb&t=2&tab=3#img3",aside_tip_id:"new_clientnews_num_tip",display:true},meizhiVote:{id:17,url:"#other_url#?type=meizhiVote",aside_tip_id:"new_meizhiVote_num_tip",display:true},meizhiLevelUp:{id:15,url:"#other_url#?type=meizhiLevelUp",aside_tip_id:"new_meizhiLevelUp_tip",display:true}};var y={itb_home:""};var W=function(ag,ae){e=ag;O=ae||$("body");var af=TbCom.process("MsgSystem","getIsReady");if(af){i()}else{TbCom.addEvent("MsgSystem","ready",function(){i()})}};var i=function(){if(R){return}if(e!="itieba"){a="_blank"}var ae=TbCom.process("User","getUserInfo");if(!ae||!ae.is_login||!ae.portrait){TbCom.process("User","getUserInfoByRequest",S)}else{S(ae)}R=true};var S=function(ae){d=ae.portrait;y.itb_home="/i/sys/jump?u="+d;for(var af in G){J[G[af]["id"]]=af}for(var ag in G){var ah=G[ag];if(typeof ah.url!="undefined"){switch(ag){case"guess":G[ag]["url"]=ah.url.replace(/#itb_home#/g,"/i/app/"+ag+"?uc="+d);break;case"invite":G[ag]["url"]=ah.url.replace(/#itb_home#/g,"/f/i/invite");break;case"meizhiVote":case"meizhiLevelUp":G[ag]["url"]=ah.url.replace(/#other_url#/g,"/encourage/get/meizhi/jump");break;default:G[ag]["url"]=ah.url.replace(/#itb_home#/g,"/i/sys/jump?u="+d)}}}g();TbCom.addEvent("MsgSystem","sys_message",T);TbCom.addEvent("MsgSystem","listenComplete",c);N();I(ae.client_msg_count)};var g=function(){var ak=J;var ae=[];ae.push('<div style="clear:both;"><ul>');for(var ah=0,af=ak.length;ah<af;ah++){ae.push('<li id="message_'+ak[ah]+'" style="display:none;"></li>')}ae.push("</ul>");ae.push('<div class="tb_msg_tip_rightpanel">');ae.push('<a href="'+y.itb_home+'&type=profile#notify" style="height:100%;" target="_self" class="setting">设置</a>');ae.push('<a title="关闭" href="#" onclick="TbCom.process(\'UserMessage\',\'clearAllData\');return false" class="close_msg_tip"></a>');ae.push('<b style="clear:both; text-align:left;"></b>');ae.push("</div></div>");var aj=$("#com_userbar").find(".u_ucenter>div"),an=aj.offset().left,al=an?an:0,ag=$("body").width();_right=ag-al-160,_right=_right>350?180:_right;var ai={content:ae.join(""),arrow_dir:"up",bubble_css:{right:_right,width:170},arrow_pos:{left:30},level:2,attr:" id='tb_message_tip_n' ",wrap:O};var am=new UiBubbleTipBase(ai);am.setFixedForMessage();ab=am.j_bubble;s=am;$("#mobile_promote_download").bind("click",function(){_.Module.use("common/component/diversionDialog",[],function(ao){ao.showDiversionDialog("webtbnews")})})};var u=function(ae){TbCom.process("MsgSystem","doSomethingAfterReady",function(){ae()})};var N=function(){var af="http://message.tieba.baidu.com/i/msg/get_data";var ae=af+"?user="+d;$.JsLoadManager.use(ae)};var o=function(ae){u(function(){switch(ae){case"favts":n();break;case"clientnews":q();break;default:ad(ae);f(ae)}})};var ad=function(ah){var ag=new Date().getTime();var ai=G[ah]["id"];if(ai!==20){var af="http://message.tieba.baidu.com/i/msg/clear_data?type="+ai+"&user="+d+"&stamp="+ag;var ae=new Image();window["itieba_msg_clearer_"+ag]=ae;ae.src=af}};var D=function(){u(function(){for(var ae in G){if(ae!="all_msg"){ad(ae)}}m()})};var ac=function(){var af=new Date().getTime();var ae="/tsmg?query=get_data&uid="+d+"&stamp="+af;$.get(ae,function(ag){if(ag&&ag.no==0){h(ag.data.ret);Q()}},"json")};var n=function(){var af=new Date().getTime();var ae="/tsmg?query=clear_data&uid="+d+"&stamp="+af;$.get(ae,function(ag){if(ag&&ag.no==0){h(0);Q()}},"json")};var q=function(){$.cookie("CLIENT_MSG_COUNT",j.clientnews,{expires:30,path:"/"});I(0)};var X=function(ae){var af=ae.join(",");ac();H(af);TbCom.process("MsgSystem","sendMsg","other","sys","all_msg",af,"default",null,false)};initItiebaMessage=X;var f=function(ae){u(function(){if(!ae||ae==""){return}TbCom.process("MsgSystem","sendMsg","all","sys",ae,"0","default",null,false)})};var m=function(){TbCom.process("MsgSystem","sendMsg","all","sys","clear_msg","all","default",null,false);TbCom.process("MsgSystem","removeMsgByMod","sys","command_listen");n();q()};var A=function(){var ae="/f?ct=486539264&cm=59202&tn=jsonUserInfo&t="+Math.random();$.get(ae,{},function(af){var ag=$.json.decode(af);if(ag.beans_num){TbCom.process("MsgSystem","sendMsg","all","sys","wealth",ag.beans_num,"default",null,false);setTimeout(function(){ad("wealth");TbCom.process("MsgSystem","removeMsg","sys","wealth")},100)}})};var c=function(ai,ah){var ag=ah.mod;var ae=J[ah.msg.type];var af=ah.msg.cnt;if(ag=="sys"&&ae=="wealth"){A();return}TbCom.process("MsgSystem","sendMsg","all",ag,ae,af,"default",null,false)};var T=function(ah,ag){if(!ag){$.console.debug("@UserMessage _renderMsg : 不需要处理！")}else{var af=ag.type,ae=ag.content;if(af&&typeof ae!="undefined"){t(af,ae)}else{$.console.debug("@UserMessage _renderMsg : 返回的数据中没有type和content")}}};var t=function(ae,af){switch(ae){case"all_msg":H(af);break;case"fans":z(af);break;case"evaluate":K(af);break;case"wealth":x(af);break;case"reply":l(af);Q();break;case"feature":aa(af);break;case"guess":V(af);break;case"atme":L(af);Q();break;case"light":Z(af);Q();break;case"invite":P(af);break;case"paperprops":b(af);case"favts":h(af);break;case"recycle":E(af);Q();break;case"clear_msg":Y(af);break;case"meizhiVote":U(af);break;case"meizhiLevelUp":v(af);break;default:$.console.debug("@UserMessage _renderMsgHandler; LCF返回的消息没有处理函数");break}};var z=function(af){var ae=parseInt(af);if(ae>0){M("fans",ae,"新粉丝")}else{F("fans")}};var K=function(ah){var ag=parseInt(ah);var ae=$("#new_evaluate_num_tip");var af="";if(ag>0){M("evaluate",ag,"新评价");af="("+ah+"新)"}else{F("evaluate")}if(ae){ae.html(af)}};var x=function(ah){var af=parseInt(ah);var ag=B;if(af>0){if(typeof ag=="string"&&(ag=="add_post")){TbCom.process("WealthSystem","postTipSetDisplay",true)}else{var ae='<div class="tb_beans_msg_tip">恭喜你，贴吧豆增收啦！<br />当前总数：<span class="tb_beans_num_tip"><b>'+ah+"</b></span>个</div>"}}};var aa=function(ah){var ag=parseInt(ah);var ae=$("#new_feature_num_tip");var af="";if(ag>0){M("feature",ag,"新精品");af="("+ah+"新)"}else{F("feature")}if(ae){ae.html(af)}};var l=function(af){var ae=parseInt(af);j.reply=ae;if(ae>0){M("reply",ae,"新回复")}else{F("reply")}};var Q=function(){var ag=j.reply+j.atme+j.light+j.recycle;if(ag>0){var ae=$("#new_reply_num_tip");var af="";af="("+ag+"新)";if(ae){ae.html(af)}}else{var ae=$("#new_reply_num_tip").html("")}};var h=function(ah){var ag=parseInt(ah);j.favts=ag;if(ag>0){var ae=$("#new_storethread_num_tip");var af="";af="("+ag+"贴有更新)";if(ae){ae.html(af)}M("favts",ag,"收藏贴有更新");$.stats.sendRequest("fr=tb0_forum&st_mod=msgsys&st_type=favtshow")}else{F("favts")}};var I=function(ag){var ae=parseInt(ag);if(ae>0){var af=$.cookie("CLIENT_MSG_COUNT");if(!af){j.clientnews=ae;$.stats.track("clientnews","ihome_v1");M("clientnews",ae,"来自客户端")}else{if(parseInt(af)!==ae){j.clientnews=ae;$.stats.track("clientnews","ihome_v1");M("clientnews",ae,"来自客户端");$.cookie("CLIENT_MSG_COUNT",0,{expires:-1,path:"/"})}else{F("clientnews")}}}else{F("clientnews")}};var E=function(af){var ae=parseInt(af);j.recycle=ae;if(ae>0){M("recycle",ae,"回收站提醒")}else{F("recycle")}};var V=function(af){var ae=parseInt(af);if(ae>0){M("guess",ae,"竞猜结果")}else{F("guess")}};var P=function(af){var ae=parseInt(af);j.invite=ae;if(ae>0){M("invite",ae,"粉丝福利卡")}else{F("invite")}};var b=function(af){var ae=parseInt(af);j.paperprops=ae;if(ae>0){M("paperprops",ae,"贴条道具信息")}else{F("paperprops")}};var w=function(af){var ae=parseInt(af);j.invite=ae;if(ae>0){M("newask",ae,"名片新请求")}else{F("newask")}};var r=function(af){var ae=parseInt(af);j.invite=ae;if(ae>0){M("newcard",ae,"新名片")}else{F("newcard")}};var U=function(af){var ae=parseInt(af);if(ae>0){M("meizhiVote",ae,"新的投票")}else{F("meizhiVote")}};var v=function(af){var ae=parseInt(af);if(ae>0){M("meizhiLevelUp",null,"妹纸，Mvp升级了！")}else{F("meizhiVote")}};var L=function(af){var ae=parseInt(af);j.atme=ae;if(ae>0){M("atme",ae,"@提到我")}else{F("atme")}};var Z=function(af){var ae=parseInt(af);j.light=ae;if(ae>0){M("light",ae,"点亮我")}else{F("light")}};var Y=function(al){var ak=ab;var aj=ak.find("li");for(var ai=0,af=aj.length;ai<af;ai++){$(aj[ai]).css("display","none")}ak.css("display","none");var ae=null;var ah="";for(var ag in G){ah=G[ag]["aside_tip_id"];if(typeof ah=="string"&&ah!=""){ae=$("#"+ah);if(ae){ae.html("");ae.css("display","none")}}}};var H=function(ak){var aj=ak.split(",");var ah=J;var ai=ah.length-1;var af;for(var ag=0,ae=aj.length;ag<ae;ag++){num=aj[ag];if(ag<ai){af=ah[ag+1];t(af,num)}}};var k=function(al){var ak=ab;var aj=ab.find("li");for(var ai=0,af=aj.length;ai<af;ai++){$(aj[ai]).css("display","none")}if(s){s.hideBubble()}var ae=null;var ah="";for(var ag in G){ah=G[ag]["aside_tip_id"];if(typeof ah=="string"&&ah!=""){ae=$("#"+ah);if(ae){ae.html("");ae.css("display","none")}}}};var p=function(ae){B=ae};var M=function(aj,ag,al){var an=$("#message_"+aj)||null;var ah=G[aj];if(ah.display==false||!an){return}var ak=ah.id;var ae=ah.url;var am="st_mod="+aj+"_tip&fr=tb0_"+e;var ai=$("<span>"+ag+"个</span>");if(aj=="clientnews"){ai=$("<span>"+ag+"条消息 </span>")}var af=$("<a>"+al+"</a>");af.attr({href:ae,target:a});af.bind("click",function(){o(aj);$.stats.sendRequest(am)});an.html("");ag!==null&&an.append(ai);an.append(af);an.css("display","block");if(s){s.showBubble()}$("#u_xiangce").find(".j_wrap").hide()};var F=function(ah){var af=$("#message_"+ah);var aj=ab;var ai=aj.find("li");af.css("display","none");var ak=true;for(var ag=0,ae=ai.length;ag<ae;ag++){if($(ai[ag]).css("display")!="none"){ak=false;break}}aj.css("display",ak?"none":"block")};var C=function(af,ae){if(!af||!(af in G)){return}G[af]["display"]=!!(ae)};this.initSys("UserMessage",["User","MsgSystem","WealthSystem"],{init:W,clearSysMsg:f,clearData:o,clearAllData:D,setWealthActionType:p,setMsgDisplay:C})})();