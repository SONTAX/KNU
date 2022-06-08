let picture1 = {
    name: "First",
    way: "local/folder1",
    //date: new Date(2011, 11, 1)
    date: "2020.05.19"
};
let picture2 = {
    name: "Second",
    way: "local/folder2",
    //date: new Date(2012, 10, 2),
    date: "2019.06.13"
};
let picture3 = {
    name: "Third",
    way: "local/folder3",
    //date: new Date(2013, 9, 3)
    date: "2018.04.07"
};
let picture4 = {
    name: "",
    way: "local/folder4",
    //date: new Date(2014, 8, 4)
    date: "2021.12.10"
};
let Gallery = [picture1, picture2, picture3, picture4];
let JSON_Gallery = [];

function stringify1(obj) {
    console.log("First method:\n");
    for (let i = 0; i < obj.length; i++) {
        let test = JSON.stringify(obj[i]);
        JSON_Gallery[i] = test;
        console.log(JSON_Gallery[i]);
    }
    console.log("\n\n");
}

function stringify2(obj) {
    console.log("Second method:\n");
    for (let i = 0; i < obj.length; i++) {
        let test = JSON.stringify(obj[i], ["name"]);
        JSON_Gallery[i] = test;
        console.log(JSON_Gallery[i]);
    }
    console.log("\n\n");
}

function stringify3(obj) {
    let flag = true;
    console.log("Third method:\n");
    for (let i = 0; i < obj.length; i++) {
        let temp = JSON.stringify(obj[i], function (key, value) {
            if ((key === "name") && (value === "")) {
                flag = false;
                return undefined;
            }
            if (flag) {
                return value
            } else {
                return undefined;
            }
        });
        JSON_Gallery[i] = temp;
        console.log(JSON_Gallery[i]);
    }
    console.log("\n\n");
}

function parse(obj) {
    for (let i = 0; i < obj.length; i++) {
        JSON_Gallery[i] = JSON.parse(obj[i], function (key, value) {
            if (key === "date") {
                return new Date(value);
            } else {
                return value;
            }
        });
        console.log(JSON_Gallery[i]);
    }
    console.log("\n\n");
}

stringify1(Gallery);
parse(JSON_Gallery);
stringify2(Gallery);
parse(JSON_Gallery);
stringify3(Gallery);
parse(JSON_Gallery);