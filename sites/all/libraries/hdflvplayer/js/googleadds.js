
var pagearray=new Array();
var timerout1 ;
var timerout;
var timerout2;
var timerout3;
pageno =0 ;

//postadd
setTimeout('onplayerloaded()',10000);
var path =window.location.pathname;

var substr = path.split('/');
pagearray[0]='/'+substr[1]+'/'+substr[2]+'/node/googleads';
function getFlashMovie(movieName)
{
    var isIE = navigator.appName.indexOf("Microsoft") != -1;
    return (isIE) ? window[movieName] : document[movieName];
}

function googleclose()
{
    if(document.all)
    {
        document.all.IFrameName.src="";
    }
    else
    {
        frames['IFrameName'].location.href="";
    }
    document.getElementById('lightm').style.display="none";
    clearTimeout();

    setTimeout('bindpage(0)', ropen);
}

function onplayerloaded()
{
    pageno=1;
    X= findPosX(document.getElementById('mediaspace'));
    Y= findPosY(document.getElementById('mediaspace'));
    w=parseInt(document.getElementById('mediaspace').style.width);

    h=parseInt(document.getElementById('mediaspace').style.height);
   
    document.getElementById('lightm').style.top=Y+((h-90))+"px";
    if(w>470)
    {
        document.getElementById('lightm').style.left=((w-470)/2)+"px";
    }
    else
    {
        document.getElementById('lightm').style.left=((470-w)/2)+"px";
    }
    timerout1 =window.setTimeout('bindpage(0)', 1000);   
   
 
}

function findPosX(obj)
{
    var curleft = 0;
    if(obj.offsetParent)
        while(1)
        {
            curleft += obj.offsetLeft;
            if(!obj.offsetParent)
                break;
            obj = obj.offsetParent;
        }
    else if(obj.x)
        curleft += obj.x;
    return curleft;
}

function findPosY(obj)
{
    var curtop = 0;
    if(obj.offsetParent)
        while(1)
        {
            curtop += obj.offsetTop;
            if(!obj.offsetParent)
                break;
            obj = obj.offsetParent;
        }
    else if(obj.y)
        curtop += obj.y;
    return curtop;
}

function closediv()
{
  
    document.getElementById('lightm').style.display="none";
    clearTimeout();
    if( ropen!=''){
        setTimeout('bindpage(0)', ropen);
    }
}

function bindpage(pageno)
{   
    
    if(document.all)
    {
        document.all.IFrameName.src=pagearray[0];
    }
    else
    {     
        frames['IFrameName'].location.href=pagearray[pageno];
    }
    
    document.getElementById('closeimgm').style.display="block";
    document.getElementById('lightm').style.display="block";
    if(closeadd !='') setTimeout('closediv()', closeadd);
    
}

