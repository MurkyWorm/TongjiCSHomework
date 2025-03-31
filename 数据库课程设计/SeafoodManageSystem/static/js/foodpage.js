var jsonString = JSON.parse(document.getElementById('response_data').textContent);
var products = JSON.parse(jsonString);

var currentPage = 1;
var rowsPerPage = 20;

function displayTable(page) {
    var start = (page - 1) * rowsPerPage;
    var end = start + rowsPerPage;
    var paginatedItems = products.slice(start, end);

    var table = document.getElementById('productTable');
    table.innerHTML = "";  // 清空表格

    for (var i = 0; i < paginatedItems.length; i++) {
        var item = paginatedItems[i];
        var row = table.insertRow();
        row.setAttribute('data_product_id', item.product_id);
        row.addEventListener('click', function() {
            window.location.href = '/seafood/product/' + item.product_id + '/'; // 在点击时跳转到指定URL
        });
        var cell1 = row.insertCell(0);
        cell1.innerHTML = item.class_name;
        var cell2 = row.insertCell(1);
        cell2.innerHTML = Number(item.quantity).toFixed(3);
        var cell3 = row.insertCell(2);
        cell3.innerHTML = Number(item.lat).toFixed(3);;
        var cell4 = row.insertCell(3);
        cell4.innerHTML = Number(item.lng).toFixed(3);;
        var cell5 = row.insertCell(4);
        cell5.innerHTML = item.production_time;
        var cell6 = row.insertCell(5);
        cell6.innerHTML = item.expiration_time;
        var cell7 = row.insertCell(6);
        if (item.state == 0) {
            cell7.innerHTML = '未售出';
        }
        else {
            cell7.innerHTML = '已售出';
        }
    }
}

function setupPagination(items, wrapper, rowsPerPage) {
    wrapper.innerHTML = "";  // 清空分页控件
    var pageCount = Math.ceil(items.length / rowsPerPage);
    for (var i = 1; i <= pageCount; i++) {
        var btn = paginationButton(i);
        wrapper.appendChild(btn);
    }
}

function paginationButton(page) {
    var button = document.createElement('li');
    button.className = 'page-item';  // 添加Bootstrap的分页项类
    var link = document.createElement('a');
    link.href = '#';  // 防止页面跳转
    link.className = 'page-link';  // 添加Bootstrap的分页链接类
    link.innerText = page;

    button.appendChild(link);  // 将链接添加到列表项中

    if (currentPage === page) {
        button.classList.add('active');  // 标记当前页
    }

    link.addEventListener('click', function (e) {
        e.preventDefault();  // 防止链接的默认操作
        currentPage = page;
        displayTable(currentPage);

        document.querySelectorAll('.pagination li').forEach(function(item) {
            item.classList.remove('active');
        });

        button.classList.add('active');
    });

    return button;
}

// 初始化
document.addEventListener('DOMContentLoaded', function () {
    displayTable(1);
    setupPagination(products, document.getElementById('pagination'), rowsPerPage);
});


var timeDropdown = document.getElementById('timeDropdown');
var statusDropdown = document.getElementById('statusDropdown');

var timeFilter = document.getElementById('timeFilterjing');
var statusFilter = document.getElementById('statusFilterjing');


document.addEventListener('DOMContentLoaded', function() {
    // 查找所有下拉菜单项
    document.querySelectorAll('.dropdown-menu li a').forEach(function(item) {
        item.addEventListener('click', function(e) {
            e.preventDefault(); // 防止链接默认动作
            var text = this.textContent; // 获取点击项的文本内容
            var dropdown = this.closest('.dropdown'); // 找到最近的.dropdown父元素
            dropdown.querySelector('.dropdown-toggle').textContent = text + ' '; // 更新按钮文本
            dropdown.querySelector('.dropdown-toggle').appendChild(document.createElement('span')).className = 'caret'; // 重新添加小箭头
            if (dropdown.querySelector('.dropdown-toggle').id == 'timeDropdown') {
                timeFilter.value = text;
                console.log(timeFilter.value);
            }
            else {
                statusFilter.value = text;
                console.log(statusFilter.value);
            }
        });
    });
});
