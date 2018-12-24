dirX=dirY = 0;
greedSize = 15; //greed size
tilesX = Math.floor(window.innerWidth/greedSize);
tilesY = Math.floor(window.innerHeight/greedSize);
headX=tilesX/2; //start tile X
headY=tilesY/2; //start tile Y
// appleX=appleY = 27; //apple position
appleX=Math.floor(Math.random()*tilesX); //apple position X
appleY=Math.floor(Math.random()*tilesY); //apple position Y
trail = []; //trail array
tail = 3; //tail length
pts = 0; //points
fps = 15; //frames per second
level = 1;

window.onload=function() {
	canv=document.getElementById("canvas");
	ctx=canv.getContext("2d");
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;
	document.addEventListener("keydown",moveDirection);
	setInterval(gameLogic,1000/fps);
}


function gameLogic() {
	makeMove();
	borderCheck();
	drawSnake();
	moveTail();
	spawnAndCheckApple();
}

function moveDirection(evt) {
	switch(evt.keyCode) {
		case 37: //for ARROW_LEFT
		case 65: //for key A
			if(dirX!=1) {
				dirX=-1; dirY=0;
			}
			break;
		case 38: //for ARROW_UP
		case 87: //for key W
			if(dirY!=1) {
				dirX=0; dirY=-1;
			}
			break;
		case 39: //for ARROW_RIGHT
		case 68: //for key D
			if(dirX!=-1) {
				dirX=1; dirY=0;
			}
			break;
		case 40: //for ARROW_DOWN
		case 83: //for key S
			if(dirY!=-1) {
				dirX=0; dirY=1;
			}
			break;
	}
}

function makeMove() {
	headX+=dirX;
	headY+=dirY;
}

function moveTail() {
	trail.push({x:headX,y:headY});
	while(trail.length>tail) {
		trail.shift();
	}
}

function borderCheck() {
	switch (level) {
		case 1:
			if(headX<0) headX = tilesX-1;
			if(headX>tilesX-1) headX = 0;
			if(headY<0) headY = tilesY-1;
			if(headY>tilesY) headY = 0;
			break;
		default:
			// statements_def
			break;
	}
}

function drawSnake() {
	ctx.fillStyle="black";
	ctx.fillRect(0,0,canv.width,canv.height);
	
	// showGrid();
	
	ctx.fillStyle="white";
	for(var i=0;i<trail.length;i++) {
		if(i==trail.length-1) {
			ctx.fillStyle="yellow";
		}
		ctx.fillRect(trail[i].x*greedSize,trail[i].y*greedSize,greedSize-2,greedSize-2);
		if(trail[i].x==headX && trail[i].y==headY) {
			tail = 3;
			setStartPosition();
		}
	}
}

function spawnAndCheckApple() {
	if(headX==appleX && headY==appleY) {
		tail++;
		pts++;
		appleX=Math.floor(Math.random()*tilesX);
		appleY=Math.floor(Math.random()*tilesY);
	}
	ctx.fillStyle="green";
	ctx.fillRect(appleX*greedSize,appleY*greedSize,greedSize-2,greedSize-2);
}

function showGrid() {
	for (var y = 0; y < tilesY; y++) {
		for (var x = 0; x < tilesX; x++) {
			ctx.strokeStyle="green";
			ctx.strokeRect(x*greedSize, y*greedSize, greedSize, greedSize);
		}
	}
}

function setStartPosition() {
	headX=tilesX/2;
	headY=tilesY/2;
	pts=0;
	dirX=dirY = 0;
}