const findpwd = document.getElementById('findpwd');
const cantsee = document.getElementById('cantsee');
const cantsee1 = document.getElementById('cantsee1');
const reg = document.getElementById('reg');

findpwd.addEventListener('click', function () {
	if (cantsee.value == 'False') {
		cantsee.value = 'True';
	}
	else {
		cantsee.value = 'False';
	}
	if (cantsee1.value == 'False') {
		cantsee1.value = 'True';
	}
	else {
		cantsee1.value = 'False';
	}
});

reg.addEventListener('click', function () {
    window.location.href = '/REG_LOG/reg';
})
