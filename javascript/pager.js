//Paginator
function Pager(curpg, count, perpg, rangelenNum, func, elem) {


    var paginator = {
        firstPage: 0,
        prevPage: 0,
        nextPage: 0,
        lastPage: 0,
        rangePages: [],
        rangeLenNum: rangelenNum,
        curpage: curpg,
        perpage: perpg,
        pageNum: 0
    };


    if (curpg <= 0) {
        paginator.curpage = 1;
    } else if (curpg > count) {
        curpg = count;
    }

    if (perpg <= 0) {
        paginator.perpage = 5;
    }

    if (rangelenNum <= 0) {
        paginator.rangeLenNum = 8;
    }

    paginator.pageNum = Math.ceil(count / perpg);

    //init var 
    var pageRangeStart,
        pageRangeEnd,
        rangeNumHalf = rangelenNum / 2,
        prevNum,
        nextNum;

    if (curpg - rangeNumHalf > 0) {
        if (paginator.pageNum >= (curpg + rangeNumHalf)) {
            pageRangeStart = curpg - rangeNumHalf;
            pageRangeEnd = curpg + rangeNumHalf;
        } else {
            pageRangeStart = paginator.pageNum - rangelenNum + 1;
            pageRangeEnd = paginator.pageNum + 1;
        }
    } else {
        pageRangeStart = 1;
        pageRangeEnd = paginator.pageNum >= rangelenNum ? rangelenNum + 1 : paginator.pageNum + 1;
    }

    //prev next  page num
    prevNum = curpg - 1;
    nextNum = curpg + 1;
    if (prevNum > 0) {
        paginator.prevPage = prevNum;
        paginator.firstPage = 1;
    } else {
        paginator.prevPage = 0;
        paginator.firstPage = 0;
    }

    if (nextNum <= paginator.pageNum) {
        paginator.nextPage = nextNum;
        paginator.lastPage = paginator.pageNum;
    } else {
        paginator.nextPage = 0;
        paginator.lastPage = 0;
    }


    paginator.rangePages = [];
    if (pageRangeStart < 1) {
        pageRangeStart = 1;
    }
    

    var pager = '<ul class="pagination">';
    if(paginator.prevPage != 0){
        pager += '<li>\
                    <a  href="javascript:void(0);" \
                    onClick="'+func+'('+paginator.firstPage+','+paginator.perpage+');">首页</a>\
                </li>\
                <li>\
                    <a  href="javascript:void(0);" \
                    onClick="'+func+'('+paginator.prevPage+','+paginator.perpage+');">上一页</a>\
                </li>';
    }

    for (var i = pageRangeStart; i < pageRangeEnd; i++) {
        // paginator.rangePages.push(i);
        if(i != paginator.curpage){
            pager+='<li>\
                        <a  href="javascript:void(0);" \
                        onClick="'+func+'('+i+','+paginator.perpage+');">'+i+'</a>\
                    </li>';
            } else {
                pager += '<li class="disabled">\
                        <span>'+i+'</span>\
                    </li>';
            }
    }

    if(paginator.nextPage != 0){
        pager += '<li>\
                    <a  href="javascript:void(0);" \
                    onClick="'+func+'('+paginator.nextPage+','+paginator.perpage+');">下一页</a>\
                </li>\
                <li>\
                    <a  href="javascript:void(0);" \
                    onClick="'+func+'('+paginator.lastPage+','+paginator.perpage+');">末页</a>\
                </li>';
    }

    pager += '</ul>';

    document.getElementById(elem).innerHTML = pager;
}