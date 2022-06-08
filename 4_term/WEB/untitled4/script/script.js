import * as shop from "./shop.js";

const addBtn = document.querySelector(".btn-add"),
    buyBtn = document.querySelector(".btn-buy"),
    textArea = document.querySelector("#textArea"),
    textArea1 = document.querySelector("#shop-check"),
    closeModal = document.querySelectorAll("[data-close]"),
    modal = document.querySelector("#modal"),
    modal2 = document.querySelector("#modal2"),
    bank = document.querySelector("#money");

class Product {
    constructor(name, count) {
        this.name = name;
        this.count = count;
    }
}

const showGoods = (selector, item) => {
    document.querySelector(selector).value = shop.showCount(item);
};

showGoods(".product-beer", "beer");
showGoods(".product-pepsi", "pepsi");
showGoods(".product-chips", "chips");

bank.value = shop.showBank();

addBtn.addEventListener("click", () => {
    const item = document.querySelector('input[type="radio"]:checked').value;
    const count = document.querySelector("#buyProducts");
    const product = new Product(item, +count.value);

    if (shop.checkCount(product) && count.value !== "") {
        textArea.innerHTML += `${item} : ${+count.value} psc \n`;
        document.querySelector(`.product-${product.name}`).value = shop.showCount(
            product.name
        );
    } else {
        modal.style.display = "block";
        addBtn.setAttribute("disabled", "disabled");
        buyBtn.setAttribute("disabled", "disabled");
    }
    count.value = null;
});

buyBtn.addEventListener("click", () => {
    const bankValue = parseInt(bank.value);
    shop.sell();
    document.querySelector("#money").value = shop.showBank();
    textArea1.textContent = `${textArea.innerHTML} Total: ${
        parseInt(bank.value) - bankValue
    } grn`;
    textArea.textContent = null;
});

closeModal.forEach((item) => {
    item.addEventListener("click", () => {
        modal.style.display = "none";
        addBtn.removeAttribute("disabled", "disabled");
        buyBtn.removeAttribute("disabled", "disabled");
    });
});

window.addEventListener("click", (e) => {
    const target = e.target;
    if (target === modal) {
        modal.style.display = "none";
        addBtn.removeAttribute("disabled", "disabled");
        buyBtn.removeAttribute("disabled", "disabled");
    }
});