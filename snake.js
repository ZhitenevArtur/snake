dirX=dirY = 0; //direction
greedSize = 15; //greed size
tilesX = Math.floor(500/greedSize);
tilesY = Math.floor(800/greedSize);
headX=Math.floor(tilesX/2); //start tile X
headY=Math.floor(tilesY/2); //start tile Y
// appleX=appleY = 27; //apple position
appleX=Math.floor(Math.random()*tilesX); //apple position X
appleY=Math.floor(Math.random()*tilesY); //apple position Y

trail = []; //trail array
block = []; //blocks array

tail = 3; //tail length
pts = 0; //points
fps = 15; //frames per second
level = 1;
info = 0;
grid = 0;

window.onload=function() {
	canv=document.getElementById("canvas");
	ctx=canv.getContext("2d");
	canvas.width = 500;
	canvas.height = 800;
	// canvas.width = document.body.clientWidth;
	// canvas.height = document.body.clientHeight;
	document.addEventListener("keydown",moveDirection);
	document.addEventListener("resize", resizeCanvas, false);
	// document.addEventListener("resize",alert("resize"));
	blockGenerator();
	setInterval(gameLogic,1000/fps);

}

function resizeCanvas() {
	canvas.width = window.innerWidth-200;
	canvas.height = window.innerHeight;
	tilesX = Math.floor((window.innerWidth-200)/greedSize);
	tilesY = Math.floor(window.innerHeight/greedSize);
}

function gameLogic() {
	// document.addEventListener("resize", resizeCanvas, false);
	makeMove();
	borderCheck();
	drawSnake();
	moveTail();
	spawnAndCheckBlock();
	spawnAndCheckApple();
	if(info==1){
		showInfo();
	}
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
	
	if(grid==1){
		showGrid();
	}
	
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
			ctx.strokeRect(x*greedSize, y*greedSize, greedSize-2, greedSize-2);
		}
	}
}

function setStartPosition(reBlock) {
	headX=Math.floor(tilesX/2); //start tile X
	headY=Math.floor(tilesY/2); //start tile Y
	pts=0;
	dirX=dirY = 0;
	if(reBlock==1){
		block = [];
		blockGenerator();
	}
	// delete block;
	// blockGenerator();
}

function blockGenerator() {
	for (var k = 0; k < 15; k++) {
		block.push({x:Math.floor(Math.random()*tilesX),y:Math.floor(Math.random()*tilesY)});
		for (var i = 0; i < 5; i++) {
			if(randomInteger(0, 1)==0){
				if(randomInteger(0, 1)==0){
					block.push({x:block[block.length-1].x, y:block[block.length-1].y-1});
				}
				else{
					block.push({x:block[block.length-1].x, y:block[block.length-1].y+1});
				}
			}
			else{
				if(randomInteger(0, 1)==0){
					block.push({x:block[block.length-1].x-1, y:block[block.length-1].y});
				}
				else{
					block.push({x:block[block.length-1].x+1, y:block[block.length-1].y});
				}
			}
		}
	}
}

function spawnAndCheckBlock(){

	ctx.fillStyle="grey";
	for (var i = 0; i < block.length; i++) {
		ctx.fillRect(block[i].x*greedSize,block[i].y*greedSize,greedSize-2,greedSize-2);
		if(headX==block[i].x && headY==block[i].y) {
			tail = 3;
			setStartPosition(1);
		}
	}
}

function randomInteger(min, max) {
	var rand = min - 0.5 + Math.random() * (max - min + 1)
	rand = Math.round(rand);
	return rand;
}

function showInfo() {
	document.getElementById('pts_table').innerHTML = ("PTS: " + pts + "<br>" +
		"headX: " + headX + "<br>" + "headY: " + headY + "<br>" +
		"appleX: " + appleX + "<br>" + "appleY: " + appleY + "<br>" +
		"dirX: " + dirX +"<br>" +"dirY: " +dirY + "<br>" +
		"canvas.width: " + canvas.width + "<br>" + "canvas.height: " + canvas.height);
}