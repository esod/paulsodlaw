var tWidth='530px';                                    // width (in pixels)
var tHeight='25px';                                    // height (in pixels)
var tcolour='#ffffff';                                 // background colour:
var moStop=true;                                       // pause on mouseover (true or false)
var fontfamily = '"Trebuchet MS", Arial, sans-serif';  // font for content
var tSpeed=2;                                          // scroll speed (1 = slow, 5 = fast)

// enter your ticker content here (use \/ and \' in place of / and ' respectively)
var content='Breaking News about Our Office!';
var automodal='Click <a href="breaking-news" class="automodal"><strong><u>HERE!</u></strong></a> to find out more!';

// Simple Marquee / Ticker Script
// copyright 3rd January 2006, Stephen Chapman
// permission to use this Javascript on your web page is granted
// provided that all of the below code in this script (including this
// comment) is used without any alteration
var cps=tSpeed; var aw, mq; var fsz = parseInt(tHeight) - 4; 
function startticker(){
  if (document.getElementById) {
    var tick = '<a href="breaking-news" class="automodal automodal-processed">';
    tick += '<div style="position:relative;width:'+tWidth+';height:'+tHeight+';overflow:hidden;background-color:'+tcolour+'"'; 
    if (moStop) tick += ' onmouseover="cps=0" onmouseout="cps=tSpeed">'; 
    tick +='<div id="mq" style="position:absolute;left:0px;top:0px;font-family:'+fontfamily+';font-size:'+fsz+'px;white-space:nowrap;">';
    tick +='<\/div><\/div></a>'; 

    document.getElementById('ticker').innerHTML = tick; 
    mq = document.getElementById("mq"); 
    mq.style.left=(parseInt(tWidth)+10)+"px"; 
    mq.innerHTML='<span id="tx">'+content+'<\/span>'; 
    aw = document.getElementById("tx").offsetWidth; lefttime=setInterval("scrollticker()",50);
  }
}
function scrollticker(){
  mq.style.left = (parseInt(mq.style.left)>(-10 - aw)) ? parseInt(mq.style.left)-cps+"px" : parseInt(tWidth)+10+"px";
} 
window.onload=startticker;
                  
