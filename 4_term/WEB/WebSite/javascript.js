    var boxSizeArray = [1,1,1,1,1,1,1];
	
	var arrow_offsetX = -5;	
	var arrow_offsetY = 0;	
	
	var arrow_offsetX_firefox = -6;	
	var arrow_offsetY_firefox = -13; 
	
	var verticalSpaceBetweenListItems = 3;	
											
	var initShuffleItems = true;	

	var indicateDestionationByUseOfArrow = true;	
	
	
	var lockedAfterDrag = true;	
	
	var dragDropTopContainer = false;
	var dragTimer = -1;
	var dragContentObj = false;
	var contentToBeDragged = false;	
	var contentToBeDragged_src = false;	
	var contentToBeDragged_next = false; 	
	var destinationObj = false;	
	var dragDropIndicator = false;	
	var ulPositionArray = new Array();
	var mouseoverObj = false;	
	
	var MSIE = navigator.userAgent.indexOf('MSIE')>=0?true:false;
	var navigatorVersion = navigator.appVersion.replace(/.*?MSIE (\d\.\d).*/g,'$1')/1;
	var destinationBoxes = new Array();
	var indicateDestinationBox = false;
		
	function getTopPos(inputObj)
	{		
	  var returnValue = inputObj.offsetTop;
	  while((inputObj = inputObj.offsetParent) != null){
	  	if(inputObj.tagName!='html')returnValue += inputObj.offsetTop;
	  }
	  return returnValue;
	}
	
	function getLeftPos(inputObj)
	{
	  var returnValue = inputObj.offsetLeft;
	  while((inputObj = inputObj.offsetParent) != null){
	  	if(inputObj.tagName!='html')returnValue += inputObj.offsetLeft;
	  }
	  return returnValue;
	}
		
	function cancelEvent()
	{
		return false;
	}
	function initDrag(e)	
	{
		if(document.all)e = event;
		if(lockedAfterDrag && this.parentNode.id!='allItems')return;
		var st = Math.max(document.body.scrollTop,document.documentElement.scrollTop);
		var sl = Math.max(document.body.scrollLeft,document.documentElement.scrollLeft);
		
		
		
		dragTimer = 0;
		dragContentObj.style.left = e.clientX + sl + 'px';
		dragContentObj.style.top = e.clientY + st + 'px';
		contentToBeDragged = this;
		contentToBeDragged_src = this.parentNode;
		contentToBeDragged_next = false;
		if(this.nextSibling){
			contentToBeDragged_next = this.nextSibling;
			if(!this.tagName && contentToBeDragged_next.nextSibling)contentToBeDragged_next = contentToBeDragged_next.nextSibling;
		}
		timerDrag();
		return false;
	}
	
	function everythingIsCorrect()
	{	
	document.getElementById('right').style.display = 'block';
	}
	
	
	function timerDrag()
	{
		if(dragTimer>=0 && dragTimer<10){
			dragTimer++;
			setTimeout('timerDrag()',10);
			return;
		}
		if(dragTimer==10){
			dragContentObj.style.display='block';
			dragContentObj.appendChild(contentToBeDragged);
		}
	}
	
	function moveDragContent(e)
	{
		if(dragTimer<10){
			if(contentToBeDragged){
				if(contentToBeDragged_next){
					contentToBeDragged_src.insertBefore(contentToBeDragged,contentToBeDragged_next);
				}else{
					contentToBeDragged_src.appendChild(contentToBeDragged);
				}	
			}
			return;
		}
		if(document.all)e = event;
		var st = Math.max(document.body.scrollTop,document.documentElement.scrollTop);
		var sl = Math.max(document.body.scrollLeft,document.documentElement.scrollLeft);
		
		
		dragContentObj.style.left = e.clientX + sl + 'px';
		dragContentObj.style.top = e.clientY + st + 'px';
		
		if(mouseoverObj)mouseoverObj.className='';
		destinationObj = false;
		dragDropIndicator.style.display='none';
		if(indicateDestinationBox)indicateDestinationBox.style.display='none';
		var x = e.clientX + sl;
		var y = e.clientY + st;
		var width = dragContentObj.offsetWidth;
		var height = dragContentObj.offsetHeight;
		
		var tmpOffsetX = arrow_offsetX;
		var tmpOffsetY = arrow_offsetY;
		if(!document.all){
			tmpOffsetX = arrow_offsetX_firefox;
			tmpOffsetY = arrow_offsetY_firefox;
		}

		for(var no=0;no<ulPositionArray.length;no++){
			var ul_leftPos = ulPositionArray[no]['left'];	
			var ul_topPos = ulPositionArray[no]['top'];	
			var ul_height = ulPositionArray[no]['height'];
			var ul_width = ulPositionArray[no]['width'];
			
			if((x+width) > ul_leftPos && x<(ul_leftPos + ul_width) && (y+height)> ul_topPos && y<(ul_topPos + ul_height)){
				var noExisting = ulPositionArray[no]['obj'].getElementsByTagName('LI').length;
				if(indicateDestinationBox && indicateDestinationBox.parentNode==ulPositionArray[no]['obj'])noExisting--;
				if(noExisting<boxSizeArray[no-1] || no==0){
					dragDropIndicator.style.left = ul_leftPos + tmpOffsetX + 'px';
					var subLi = ulPositionArray[no]['obj'].getElementsByTagName('LI');
					for(var liIndex=0;liIndex<subLi.length;liIndex++){
						var tmpTop = getTopPos(subLi[liIndex]);
						if(!indicateDestionationByUseOfArrow){
							if(y<tmpTop){
								destinationObj = subLi[liIndex];
								indicateDestinationBox.style.display='block';
								subLi[liIndex].parentNode.insertBefore(indicateDestinationBox,subLi[liIndex]);
								break;
							}
						}else{							
							if(y<tmpTop){
								destinationObj = subLi[liIndex];
								dragDropIndicator.style.top = tmpTop + tmpOffsetY - Math.round(dragDropIndicator.clientHeight/2) + 'px';
								dragDropIndicator.style.display='block';
								break;
							}	
						}					
					}
					
					if(!indicateDestionationByUseOfArrow){
						if(indicateDestinationBox.style.display=='none'){
							indicateDestinationBox.style.display='block';
							ulPositionArray[no]['obj'].appendChild(indicateDestinationBox);
						}
						
					}else{
						if(subLi.length>0 && dragDropIndicator.style.display=='none'){
							dragDropIndicator.style.top = getTopPos(subLi[subLi.length-1]) + subLi[subLi.length-1].offsetHeight + tmpOffsetY + 'px';
							dragDropIndicator.style.display='block';
						}
						if(subLi.length==0){
							dragDropIndicator.style.top = ul_topPos + arrow_offsetY + 'px'
							dragDropIndicator.style.display='block';
						}
					}
					
					if(!destinationObj)destinationObj = ulPositionArray[no]['obj'];
					mouseoverObj = ulPositionArray[no]['obj'].parentNode;
					mouseoverObj.className='mouseover';
					return;
				}
			}
		}
	}
	
	function checkAnswers()
	{
		
		for(var no=0;no<destinationBoxes.length;no++){
			var subLis = destinationBoxes[no].getElementsByTagName('LI');
			if(subLis.length<boxSizeArray[no])return;	
			
			for(var no2=0;no2<subLis.length;no2++){
				if(subLis[no2].className=='wrongAnswer')return;
			}		
		}
		
		everythingIsCorrect();
		
		
	}
	
	function dragDropEnd(e)
	{
		if(dragTimer==-1)return;
		if(dragTimer<10){
			dragTimer = -1;
			return;
		}
		dragTimer = -1;
		if(document.all)e = event;		
		if(destinationObj){
			var groupId = contentToBeDragged.getAttribute('groupId');
			if(!groupId)groupId = contentToBeDragged.groupId;
			
			var destinationToCheckOn = destinationObj;
			if(destinationObj.tagName!='UL'){
				destinationToCheckOn = destinationObj.parentNode;
			}
			
			var answerCheck = false;
			if(groupId == destinationToCheckOn.id){
				contentToBeDragged.className = 'correctAnswer';		
				answerCheck=true;	
			}else{
				contentToBeDragged.className = 'wrongAnswer';
			}
			if(destinationObj.id=='allItems' || destinationObj.parentNode.id=='allItems')contentToBeDragged.className='';
			
			
			if(destinationObj.tagName=='UL'){
				destinationObj.appendChild(contentToBeDragged);
			}else{
				destinationObj.parentNode.insertBefore(contentToBeDragged,destinationObj);
			}
			mouseoverObj.className='';
			destinationObj = false;
			dragDropIndicator.style.display='none';
			if(indicateDestinationBox){
				indicateDestinationBox.style.display='none';
				document.body.appendChild(indicateDestinationBox);
			}
						
			contentToBeDragged = false;
			
			if(answerCheck)checkAnswers();	
			
			return;
		}	
		if(contentToBeDragged_next){
			contentToBeDragged_src.insertBefore(contentToBeDragged,contentToBeDragged_next);
		}else{
			contentToBeDragged_src.appendChild(contentToBeDragged);
		}
		contentToBeDragged = false;
		dragDropIndicator.style.display='none';
		if(indicateDestinationBox){
			indicateDestinationBox.style.display='none';
			document.body.appendChild(indicateDestinationBox);
			
		}		
		mouseoverObj = false;
		
	}
	
	function saveDragDropNodes()
	{
		var saveString = "";
		var uls = dragDropTopContainer.getElementsByTagName('UL');
		for(var no=0;no<uls.length;no++){	
			var lis = uls[no].getElementsByTagName('LI');
			for(var no2=0;no2<lis.length;no2++){
				if(saveString.length>0)saveString = saveString + ";";
				saveString = saveString + uls[no].id + '|' + lis[no2].id;
			}	
		}		
		
		document.getElementById('saveContent').innerHTML = '<h1>Ready to save these nodes:</h1> ' + saveString.replace(/;/g,';<br>') + '<p>Format: ID of ul |(pipe) ID of li;(semicolon)</p><p>You can put these values into a hidden form fields, post it to the server and explode the submitted value there</p>';
		
	}
	
	function initDragDropScript()
	{
		dragContentObj = document.getElementById('dragContent');
		dragDropIndicator = document.getElementById('dragDropIndicator');
		dragDropTopContainer = document.getElementById('dhtmlgoodies_dragDropContainer');
		document.documentElement.onselectstart = cancelEvent;;
		var listItems = dragDropTopContainer.getElementsByTagName('LI');	
		var itemHeight = false;
		for(var no=0;no<listItems.length;no++){
			listItems[no].onmousedown = initDrag;
			listItems[no].onselectstart = cancelEvent;
			if(!itemHeight)itemHeight = listItems[no].offsetHeight;
			if(MSIE && navigatorVersion/1<6){
				listItems[no].style.cursor='hand';
			}			
		}
		
		var mainContainer = document.getElementById('dhtmlgoodies_mainContainer');
		var uls = mainContainer.getElementsByTagName('UL');
		itemHeight = itemHeight + verticalSpaceBetweenListItems;
		for(var no=0;no<uls.length;no++){
			uls[no].style.height = itemHeight * boxSizeArray[no]  + 'px';
			destinationBoxes[destinationBoxes.length] = uls[no];
		}
		
		var leftContainer = document.getElementById('dhtmlgoodies_listOfItems');
		var itemBox = leftContainer.getElementsByTagName('UL')[0];
		
		document.documentElement.onmousemove = moveDragContent;	
		document.documentElement.onmouseup = dragDropEnd;	
		
		var ulArray = dragDropTopContainer.getElementsByTagName('UL');
		for(var no=0;no<ulArray.length;no++){
			ulPositionArray[no] = new Array();
			ulPositionArray[no]['left'] = getLeftPos(ulArray[no]);	
			ulPositionArray[no]['top'] = getTopPos(ulArray[no]);	
			ulPositionArray[no]['width'] = ulArray[no].offsetWidth;
			ulPositionArray[no]['height'] = ulArray[no].clientHeight;
			ulPositionArray[no]['obj'] = ulArray[no];
		}
		
		if(initShuffleItems){
			var allItemsObj = document.getElementById('allItems');
			var initItems = allItemsObj.getElementsByTagName('LI');
			
			for(var no=0;no<(initItems.length*10);no++){
				var itemIndex = Math.floor(Math.random()*initItems.length);
				allItemsObj.appendChild(initItems[itemIndex]);
			}
		}
		if(!indicateDestionationByUseOfArrow){
			indicateDestinationBox = document.createElement('LI');
			indicateDestinationBox.id = 'indicateDestination';
			indicateDestinationBox.style.display='none';
			document.body.appendChild(indicateDestinationBox);
		}		
		
	}
	window.onload = initDragDropScript;
	
	var numQues = 7;

    var numChoi = 3;

    var answers = new Array(7);

    answers[0] = "ClearDevice";
    answers[1] = "SetBkColor";
    answers[2] = "SetFillStyle";
    answers[3] = "Graph";
	answers[4] = "16";
	answers[5] = "line";
	answers[6] = "Точка";


    function getScore(form) {
    var score = 0;
    var currElt;
    var currSelection;
    for (i=0; i<numQues; i++) {
      currElt = i*numChoi;
      for (j=0; j<numChoi; j++) {
        currSelection = form.elements[currElt + j];
        if (currSelection.checked) {
          if (currSelection.value == answers[i]) {
           score++;
           break;                                }
                                   }
                                }
                              }
    score = Math.round(score/numQues*100);
    form.percentage.value = score + " балів";
    var correctAnswers = "";
    for (i=1; i<=numQues; i++) {
     correctAnswers += i + ". " + answers[i-1] + "\r\n";
                               }
    form.solutions.value = correctAnswers;
                            }
  
	
	