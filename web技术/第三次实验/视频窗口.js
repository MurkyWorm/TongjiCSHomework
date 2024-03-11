const jingVideo = document.getElementById('jingVideo');
const playButton = document.getElementById('playButton');
const totalProgress = document.getElementById('totalProgress');
const currentProgress = document.getElementById('currentProgress');
const timeDisplay = document.getElementById('timeDisplay');
const bottomPlayButton = document.getElementById('bottomPlayButton');
const volumeButton = document.getElementById('volumeButton');
const volumeBack = document.getElementById('volumeBack');
const volumeSpace = document.getElementById('volumeSpace');
const volumeStrip = document.getElementById('volumeStrip');
const rateButton = document.getElementById('rateButton');
const rateChoice1 = document.getElementById('rateChoice1');
const rateChoice2 = document.getElementById('rateChoice2');
const rateChoice3 = document.getElementById('rateChoice3');
const rateChoice4 = document.getElementById('rateChoice4');
const rateChoice5 = document.getElementById('rateChoice5');
const rateChoice6 = document.getElementById('rateChoice6');
const fullScreenButton = document.getElementById('fullScreenButton');

// 以下是通过点击视频窗口或视频中间的播放暂停键实现视频的播放和暂停
playButton.addEventListener('mouseover', function() {
	playButton.style.color='white';
})
playButton.addEventListener('mouseout', function() {
	playButton.style.color='rgba(200, 200, 200, 1)';
})
playButton.addEventListener('click', function() {
	if (jingVideo.paused) {
	    jingVideo.play();
	    playButton.innerHTML = '❚❚';
		bottomPlayButton.innerHTML = '❚❚';
	} 
	else {
	    jingVideo.pause();
	    playButton.innerHTML = '►';
		bottomPlayButton.innerHTML = '►';
	}
});
jingVideo.addEventListener('click', function() {
	if (jingVideo.paused) {
	    jingVideo.play();
	    playButton.innerHTML = '❚❚';
		bottomPlayButton.innerHTML = '❚❚';
	} 
	else {
	    jingVideo.pause();
	    playButton.innerHTML = '►';
		bottomPlayButton.innerHTML = '►';
	}
});

// 以下实现视频的进度功能，包括时间显示，进度条显示，通过进度条改变进度
function showCurrent() {
	let currentTime = 0,currentMins = 0,currentSeconds = 0;
	let totalTime = 0,totalMins = 0,totalSeconds = 0;
				
	currentTime = jingVideo.currentTime;
	currentMins = parseInt(currentTime / 60);
	currentSeconds = parseInt(currentTime) % 60;//求当前时间的分和秒
				
	totalTime = jingVideo.duration;
	totalMins = parseInt(totalTime / 60);
	totalSeconds = parseInt(totalTime) % 60;//求当前时间的分和秒
				
	timeDisplay.innerHTML = currentMins.toString().padStart(2,'0') + ":" + currentSeconds.toString().padStart(2,'0') + 
	"/" + totalMins.toString().padStart(2,'0') + ":" + totalSeconds.toString().padStart(2,'0');//显示时间
	currentProgress.style.width=currentTime/totalTime*98 + "%";//显示进度条
}
setInterval(showCurrent,100);//显示当前时间和进度条
totalProgress.addEventListener('click', function() {
	var rect = this.getBoundingClientRect();
	var x = event.clientX - rect.left;
	jingVideo.currentTime=x/rect.width*jingVideo.duration;
})//调整进度

//以下是设置视频窗口左下方的播放键功能
bottomPlayButton.addEventListener('mouseover', function() {
	bottomPlayButton.style.color='white';
})
bottomPlayButton.addEventListener('mouseout', function() {
	bottomPlayButton.style.color='rgba(200, 200, 200, 1)';
})
bottomPlayButton.addEventListener('click', function() {
	if (jingVideo.paused) {
	    jingVideo.play();
		playButton.innerHTML = '❚❚';
	    bottomPlayButton.innerHTML = '❚❚';
	} 
	else {
	    jingVideo.pause();
		playButton.innerHTML = '►';
	    bottomPlayButton.innerHTML = '►';
	}
});

//以下实现音量键的相关功能
var volume=jingVideo.volume;
volumeButton.addEventListener('mouseover', function() {
	volumeButton.style.fontSize="2.5vw";
	volumeBack.style.display = "block";
	volumeSpace.style.display = "block";
	volumeStrip.style.display = "block";
	volumeStrip.style.height = volume/1*16+"%";
})
volumeButton.addEventListener('mouseout', function() {
	volumeButton.style.fontSize ="2vw";
	volumeBack.style.display = "none";
	volumeSpace.style.display = "none";
	volumeStrip.style.display = "none";
})
volumeBack.addEventListener('mouseover', function() {
	volumeButton.style.fontSize = "2.5vw";
	volumeBack.style.display = "block";
	volumeSpace.style.display = "block";
	volumeStrip.style.display = "block";
})
volumeBack.addEventListener('mouseout', function() {
	volumeButton.style.fontSize = "2vw";
	volumeBack.style.display = "none";
	volumeSpace.style.display = "none";
	volumeStrip.style.display = "none";
})
volumeSpace.addEventListener('mouseover', function() {
	volumeButton.style.fontSize = "2.5vw";
	volumeBack.style.display = "block";
	volumeSpace.style.display = "block";
	volumeStrip.style.display = "block";
})
volumeSpace.addEventListener('mouseout', function() {
	volumeButton.style.fontSize ="2vw";
	volumeBack.style.display = "none";
	volumeSpace.style.display = "none";
	volumeStrip.style.display = "none";
})
volumeStrip.addEventListener('mouseover', function() {
	volumeButton.style.fontSize ="2.5vw";
	volumeBack.style.display = "block";
	volumeSpace.style.display = "block";
	volumeStrip.style.display = "block";
})
volumeStrip.addEventListener('mouseout', function() {
	volumeButton.style.fontSize ="2vw";
	volumeBack.style.display = "none";
	volumeSpace.style.display = "none";
	volumeStrip.style.display = "none";
})//鼠标悬浮显示
volumeButton.addEventListener('click', function() {
	if(volumeButton.innerHTML == "🔊")
	{
		jingVideo.volume = 0;
		volumeButton.innerHTML = "&#128263;"
	}
	else
	{
		jingVideo.volume = volume;
		volumeButton.innerHTML = "🔊"
	}
})//静音操作
volumeSpace.addEventListener('click', function() {
	var rect = this.getBoundingClientRect();
	var y = rect.bottom - event.clientY;
	jingVideo.volume = y / rect.height;
	volume = jingVideo.volume;
	volumeStrip.style.height = y / rect.height * 16 + "%";
})

//以下实现倍速功能
rateButton.addEventListener('mouseover', function() {
	rateButton.style.fontSize="1.25vw";
	rateChoice1.style.display = "block";
	rateChoice2.style.display = "block";
	rateChoice3.style.display = "block";
	rateChoice4.style.display = "block";
	rateChoice5.style.display = "block";
	rateChoice6.style.display = "block";
})
rateButton.addEventListener('mouseout', function() {
	rateButton.style.fontSize ="1vw";
	rateChoice1.style.display = "none";
	rateChoice2.style.display = "none";
	rateChoice3.style.display = "none";
	rateChoice4.style.display = "none";
	rateChoice5.style.display = "none";
	rateChoice6.style.display = "none";
})
rateChoice1.addEventListener('mouseover', function() {
	rateButton.style.fontSize="1.25vw";
	rateChoice1.style.display = "block";
	rateChoice2.style.display = "block";
	rateChoice3.style.display = "block";
	rateChoice4.style.display = "block";
	rateChoice5.style.display = "block";
	rateChoice6.style.display = "block";
	rateChoice1.style.backgroundColor = "rgba(0, 0, 0, 1)";
	rateChoice1.style.color = "white";
})
rateChoice1.addEventListener('mouseout', function() {
	rateButton.style.fontSize ="1vw";
	rateChoice1.style.display = "none";
	rateChoice2.style.display = "none";
	rateChoice3.style.display = "none";
	rateChoice4.style.display = "none";
	rateChoice5.style.display = "none";
	rateChoice6.style.display = "none";
	rateChoice1.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
	rateChoice1.style.color = "rgba(200, 200, 200, 1)";
})
rateChoice1.addEventListener('click', function() {
	jingVideo.playbackRate = 2;
})
rateChoice2.addEventListener('mouseover', function() {
	rateButton.style.fontSize="1.25vw";
	rateChoice1.style.display = "block";
	rateChoice2.style.display = "block";
	rateChoice3.style.display = "block";
	rateChoice4.style.display = "block";
	rateChoice5.style.display = "block";
	rateChoice6.style.display = "block";
	rateChoice2.style.backgroundColor = "rgba(0, 0, 0, 1)";
	rateChoice2.style.color = "white";
})
rateChoice2.addEventListener('mouseout', function() {
	rateButton.style.fontSize ="1vw";
	rateChoice1.style.display = "none";
	rateChoice2.style.display = "none";
	rateChoice3.style.display = "none";
	rateChoice4.style.display = "none";
	rateChoice5.style.display = "none";
	rateChoice6.style.display = "none";
	rateChoice2.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
	rateChoice2.style.color = "rgba(200, 200, 200, 1)";
})
rateChoice2.addEventListener('click', function() {
	jingVideo.playbackRate = 1.75;
})
rateChoice3.addEventListener('mouseover', function() {
	rateButton.style.fontSize="1.25vw";
	rateChoice1.style.display = "block";
	rateChoice2.style.display = "block";
	rateChoice3.style.display = "block";
	rateChoice4.style.display = "block";
	rateChoice5.style.display = "block";
	rateChoice6.style.display = "block";
	rateChoice3.style.backgroundColor = "rgba(0, 0, 0, 1)";
	rateChoice3.style.color = "white";
})
rateChoice3.addEventListener('mouseout', function() {
	rateButton.style.fontSize ="1vw";
	rateChoice1.style.display = "none";
	rateChoice2.style.display = "none";
	rateChoice3.style.display = "none";
	rateChoice4.style.display = "none";
	rateChoice5.style.display = "none";
	rateChoice6.style.display = "none";
	rateChoice3.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
	rateChoice3.style.color = "rgba(200, 200, 200, 1)";
})
rateChoice3.addEventListener('click', function() {
	jingVideo.playbackRate = 1.5;
})
rateChoice4.addEventListener('mouseover', function() {
	rateButton.style.fontSize="1.25vw";
	rateChoice1.style.display = "block";
	rateChoice2.style.display = "block";
	rateChoice3.style.display = "block";
	rateChoice4.style.display = "block";
	rateChoice5.style.display = "block";
	rateChoice6.style.display = "block";
	rateChoice4.style.backgroundColor = "rgba(0, 0, 0, 1)";
	rateChoice4.style.color = "white";
})
rateChoice4.addEventListener('mouseout', function() {
	rateButton.style.fontSize ="1vw";
	rateChoice1.style.display = "none";
	rateChoice2.style.display = "none";
	rateChoice3.style.display = "none";
	rateChoice4.style.display = "none";
	rateChoice5.style.display = "none";
	rateChoice6.style.display = "none";
	rateChoice4.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
	rateChoice4.style.color = "rgba(200, 200, 200, 1)";
})
rateChoice4.addEventListener('click', function() {
	jingVideo.playbackRate = 1;
})
rateChoice5.addEventListener('mouseover', function() {
	rateButton.style.fontSize="1.25vw";
	rateChoice1.style.display = "block";
	rateChoice2.style.display = "block";
	rateChoice3.style.display = "block";
	rateChoice4.style.display = "block";
	rateChoice5.style.display = "block";
	rateChoice6.style.display = "block";
	rateChoice5.style.backgroundColor = "rgba(0, 0, 0, 1)";
	rateChoice5.style.color = "white";
})
rateChoice5.addEventListener('mouseout', function() {
	rateButton.style.fontSize ="1vw";
	rateChoice1.style.display = "none";
	rateChoice2.style.display = "none";
	rateChoice3.style.display = "none";
	rateChoice4.style.display = "none";
	rateChoice5.style.display = "none";
	rateChoice6.style.display = "none";
	rateChoice5.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
	rateChoice5.style.color = "rgba(200, 200, 200, 1)";
})
rateChoice5.addEventListener('click', function() {
	jingVideo.playbackRate = 0.75;
})
rateChoice6.addEventListener('mouseover', function() {
	rateButton.style.fontSize="1.25vw";
	rateChoice1.style.display = "block";
	rateChoice2.style.display = "block";
	rateChoice3.style.display = "block";
	rateChoice4.style.display = "block";
	rateChoice5.style.display = "block";
	rateChoice6.style.display = "block";
	rateChoice6.style.backgroundColor = "rgba(0, 0, 0, 1)";
	rateChoice6.style.color = "white";
})
rateChoice6.addEventListener('mouseout', function() {
	rateButton.style.fontSize ="1vw";
	rateChoice1.style.display = "none";
	rateChoice2.style.display = "none";
	rateChoice3.style.display = "none";
	rateChoice4.style.display = "none";
	rateChoice5.style.display = "none";
	rateChoice6.style.display = "none";
	rateChoice6.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
	rateChoice6.style.color = "rgba(200, 200, 200, 1)";
})
rateChoice6.addEventListener('click', function() {
	jingVideo.playbackRate = 0.5;
})

//以下实现全屏功能
fullScreenButton.addEventListener('mouseover', function() {
	fullScreenButton.style.fontSize="2vw";
})
fullScreenButton.addEventListener('mouseout', function() {
	fullScreenButton.style.fontSize ="1.6vw";
})
fullScreenButton.addEventListener('click', function() {
	if (jingVideo.requestFullscreen) {
	    jingVideo.requestFullscreen();
	} 
	else if (jingVideo.mozRequestFullScreen) {
	    jingVideo.mozRequestFullScreen();
	} 
	else if (jingVideo.webkitRequestFullScreen) {
	    jingVideo.webkitRequestFullScreen();
	}
})

//以下实现控制按钮显示和消失
var onScreen = 0;
jingVideo.addEventListener('mouseover', function() {
	playButton.style.display = "block";
	onScreen = 1;
})
function disappear() {
	if(onScreen == 0) {
		playButton.style.display = "none";
	}
}
jingVideo.addEventListener('mouseout', function() {
	onScreen = 0;
	setTimeout(disappear, 3000);
})