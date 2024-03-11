const playListContainer = document.getElementById('playListContainer');
const allSections = document.getElementsByTagName('li');
playListContainer.addEventListener('mouseover', function(event) {
	if (event.target.tagName === 'LI') {
		event.target.style.fontSize = "1.7vw";
  }
});
playListContainer.addEventListener('mouseout', function(event) {
	if (event.target.tagName === 'LI') {
		event.target.style.fontSize = "1.5vw";
  }
});
playListContainer.addEventListener('click', function(event) {
	if (event.target.tagName === 'LI') {
		for (let i = 0; i < allSections.length; i++) {
					allSections[i].style.color = "black";
					allSections[i].style.backgroundColor = "white";
				}
		event.target.style.color = "white";
		event.target.style.backgroundColor = "black";
		jingVideo.src = "反叛的鲁路修/" + event.target.innerHTML + ".mp4";
  }
});