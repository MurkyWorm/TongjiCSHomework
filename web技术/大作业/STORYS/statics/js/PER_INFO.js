const id = document.getElementById('id');
const user_name = document.getElementById('user_name');
const name_input = document.getElementById('name_input');
const gender_input = document.getElementById('gender_input');
const age_input = document.getElementById('age_input');
const nature_input = document.getElementById('nature_input');
const pwd_input = document.getElementById('pwd_input');
const email_input = document.getElementById('email_input');
const name = document.getElementById('name');
const gender = document.getElementById('gender');
const age = document.getElementById('age');
const nature = document.getElementById('nature');
const pwd = document.getElementById('pwd');
const email = document.getElementById('email');
const name_echo = document.getElementById('name_echo');
const gender_echo = document.getElementById('gender_echo');
const age_echo = document.getElementById('age_echo');
const nature_echo = document.getElementById('nature_echo');
const pwd_echo = document.getElementById('pwd_echo');
const email_echo = document.getElementById('email_echo');
const Return = document.getElementById('Return');

name.addEventListener('click', function () {
    if (name_input.value != "") {
        var url = '/PER_INFO/edit_name/?new_name=';
        url = url + name_input.value + '&id=' + id.innerText;
        axios.get(url)
	    .then(response => {
            console.log(response.data)
            if (response.data['result'] == '修改成功,马上跳转到登录界面') {
                user_name.innerText = " " + name_input.value;
                name_input.placeholder = name_input.value
                console.log(user_name.innerText)
                name_echo.style.color = 'green';
                name_echo.innerText = response.data['result'];
                setTimeout(function() {
                    window.location.href = '/REG_LOG/log';
                }, 2000);
            }
            else {
                name_echo.style.color = 'red';
                name_echo.innerText = response.data['result'];
            }
        })
        .catch(error => {
            console.error(error);
        });
    }
});

Return.addEventListener('click', function () {
    window.location.href = '/HOME/?choice=all&value=1';
});

gender.addEventListener('click', function () {
    if (gender_input.value != "") {
        var url = '/PER_INFO/edit_gender/?new_gender=';
        url = url + gender_input.value + '&id=' + id.innerText;
        axios.get(url)
	    .then(response => {
            console.log(response.data)
            if (response.data['result'] == '修改成功') {
                gender_input.placeholder = gender_input.value
                gender_echo.style.color = 'green';
                gender_echo.innerText = response.data['result'];
            }
            else {
                gender_echo.style.color = 'red';
                gender_echo.innerText = response.data['result'];
            }
        })
        .catch(error => {
            console.error(error);
        });
    }
});

age.addEventListener('click', function () {
    if (age_input.value != "") {
        var url = '/PER_INFO/edit_age/?new_age=';
        url = url + age_input.value + '&id=' + id.innerText;
        axios.get(url)
	    .then(response => {
            console.log(response.data)
            if (response.data['result'] == '修改成功') {
                age_input.placeholder = age_input.value
                age_echo.style.color = 'green';
                age_echo.innerText = response.data['result'];
            }
            else {
                age_echo.style.color = 'red';
                age_echo.innerText = response.data['result'];
            }
        })
        .catch(error => {
            console.error(error);
        });
    }
});

nature.addEventListener('click', function () {
    if (nature_input.value != "") {
        var url = '/PER_INFO/edit_nature/?new_nature=';
        url = url + nature_input.value + '&id=' + id.innerText;
        axios.get(url)
	    .then(response => {
            console.log(response.data)
            if (response.data['result'] == '修改成功') {
                nature_input.placeholder = nature_input.value
                nature_echo.style.color = 'green';
                nature_echo.innerText = response.data['result'];
            }
            else {
                nature_echo.style.color = 'red';
                nature_echo.innerText = response.data['result'];
            }
        })
        .catch(error => {
            console.error(error);
        });
    }
});

pwd.addEventListener('click', function () {
    if (pwd_input.value != "") {
        var url = '/PER_INFO/edit_pwd/?new_pwd=';
        url = url + pwd_input.value + '&id=' + id.innerText;
        axios.get(url)
	    .then(response => {
            console.log(response.data)
            if (response.data['result'] == '修改成功,马上跳转到登录页面') {
                pwd_input.value = "";
                pwd_echo.style.color = 'green';
                pwd_echo.innerText = response.data['result'];
                setTimeout(function() {
                    window.location.href = '/REG_LOG/log';
                }, 2000);
            }
            else {
                pwd_echo.style.color = 'red';
                pwd_echo.innerText = response.data['result'];
            }
        })
        .catch(error => {
            console.error(error);
        });
    }
});

email.addEventListener('click', function () {
    if (email_input.value != "") {
        var url = '/PER_INFO/edit_email/?new_email=';
        url = url + email_input.value + '&id=' + id.innerText;
        axios.get(url)
	    .then(response => {
            console.log(response.data)
            if (response.data['result'] == '修改成功') {
                email_input.placeholder = email_input.value
                email_echo.style.color = 'green';
                email_echo.innerText = response.data['result'];
            }
            else {
                email_echo.style.color = 'red';
                email_echo.innerText = response.data['result'];
            }
        })
        .catch(error => {
            console.error(error);
        });
    }
});