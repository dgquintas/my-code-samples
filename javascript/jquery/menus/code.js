$(document).ready(function() {
      
	// Setup the nav drop-downs
	$('#nav').nmcDropDown({
    show: {height: 'show', opacity: 'show'}
	});

	// Setup the sidebar panel drop-downs
	$('#sidebarNav').nmcDropDown({
    trigger: 'click',
    submenu_selector: 'p',
    show: {height: 'show'},
    hide: {height: 'hide'}
	});
	
});


/**
 * nmcDropDown plugin - v1.0.3
 * Author: Eli Van Zoeren
 * Copyright (c) 2009 New Media Campaigns
 * http://www.newmediacampaigns.com 
 **/
(function(a){a.fn.nmcDropDown=function(b){var c=a.extend({},a.fn.nmcDropDown.defaults,b);return this.each(function(){menu=a(this);submenus=menu.children("li:has("+c.submenu_selector+")");if(c.fix_IE){menu.css("z-index",51).parents().each(function(d){if(a(this).css("position")=="relative"){a(this).css("z-index",(d+52))}});submenus.children(c.submenu_selector).css("z-index",50)}over=function(){a(this).addClass(c.active_class).children(c.submenu_selector).animate(c.show,c.show_speed);return false};out=function(){a(this).removeClass(c.active_class).children(c.submenu_selector).animate(c.hide,c.hide_speed);return false};if(c.trigger=="click"){submenus.toggle(over,out).children(c.submenu_selector).hide()}else{if(a().hoverIntent){submenus.hoverIntent({interval:c.show_delay,over:over,timeout:c.hide_delay,out:out}).children(c.submenu_selector).hide()}else{submenus.hover(over,out).children(c.submenu_selector).hide()}}})};a.fn.nmcDropDown.defaults={trigger:"hover",active_class:"open",submenu_selector:"ul",show:{opacity:"show"},show_speed:300,show_delay:50,hide:{opacity:"hide"},hide_speed:200,hide_delay:100,fix_IE:true}})(jQuery);


/**
* hoverIntent r5 // 2007.03.27 // jQuery 1.1.2+
* <http://cherne.net/brian/resources/jquery.hoverIntent.html>
* 
* @param  f  onMouseOver function || An object with configuration options
* @param  g  onMouseOut function  || Nothing (use configuration options object)
* @author    Brian Cherne <brian@cherne.net>
*/
(function($){$.fn.hoverIntent=function(f,g){var cfg={sensitivity:7,interval:100,timeout:0};cfg=$.extend(cfg,g?{over:f,out:g}:f);var cX,cY,pX,pY;var track=function(ev){cX=ev.pageX;cY=ev.pageY;};var compare=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);if((Math.abs(pX-cX)+Math.abs(pY-cY))<cfg.sensitivity){$(ob).unbind("mousemove",track);ob.hoverIntent_s=1;return cfg.over.apply(ob,[ev]);}else{pX=cX;pY=cY;ob.hoverIntent_t=setTimeout(function(){compare(ev,ob);},cfg.interval);}};var delay=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);ob.hoverIntent_s=0;return cfg.out.apply(ob,[ev]);};var handleHover=function(e){var p=(e.type=="mouseover"?e.fromElement:e.toElement)||e.relatedTarget;while(p&&p!=this){try{p=p.parentNode;}catch(e){p=this;}}if(p==this){return false;}var ev=jQuery.extend({},e);var ob=this;if(ob.hoverIntent_t){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);}if(e.type=="mouseover"){pX=ev.pageX;pY=ev.pageY;$(ob).bind("mousemove",track);if(ob.hoverIntent_s!=1){ob.hoverIntent_t=setTimeout(function(){compare(ev,ob);},cfg.interval);}}else{$(ob).unbind("mousemove",track);if(ob.hoverIntent_s==1){ob.hoverIntent_t=setTimeout(function(){delay(ev,ob);},cfg.timeout);}}};return this.mouseover(handleHover).mouseout(handleHover);};})(jQuery);
