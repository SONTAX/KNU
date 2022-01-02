let cur_page = 1;

const page_numbers = document.querySelectorAll('.nav-page');

function hide(id){
    let page = document.getElementById("page" + id.toString())
    page.style.opacity = '0';
    page.style.display = 'none';
}

function show(id){
    let page = document.getElementById("page" + id.toString());
    page.style.opacity = '1';
    page.style.display = 'flex';
    page.scrollIntoView();
}

page_numbers.forEach(
    function(page_number, ind) {
        page_number.onclick = function () {
            let cur = ind + 1;
            hide(cur_page);
            show(cur);
            let a = document.getElementById("page-num-" + cur_page.toString())
            a.classList.remove('current-page');
            let b = document.getElementById("page-num-" + cur.toString())
            b.classList.add('current-page');
            cur_page = cur;
        }
    }
);