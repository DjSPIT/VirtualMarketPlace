const functions = require("firebase-functions");
const admin = require("firebase-admin");

admin.initializeApp(functions.config().firebase);

const db = admin.database();

// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//
// exports.helloWorld = functions.https.onRequest((request, response) => {
//   functions.logger.info("Hello logs!", {structuredData: true});
//   response.send("Hello from Firebase!");
// });

//  for login redirect
exports.loginRedirect = functions.https.onCall( (data)=>{
  //  console.log(data);
  const admin1 = "Uv3BZ2yQ24ZRhocr8ItJ55GDrz82";
  const admin2 = "rfikmcLMohMLF0Q4J8zz5XKfSfT2";
  db.ref("users/" + data.uid).set(data);
  if (data.uid == admin2) {
    return "admin.html";
  }
  if (data.uid == admin1) {
    return "admin.html";
  }
  let c = "profile.html";
  return db.ref("user_data/"+data.uid).once("value", (snap)=>{
    if (snap.val()==null) {
      console.log("true");
      c = "newuser.html";
    }
    console.log(c);
  }).then(()=>{
    return c;
  });
});

/*
exports.sell = functions.https.onCall( (dat)=>{
//  console.log(dat.itemId);
//  console.log(dat.sellerId);
//  console.log(dat.quant);
//  console.log(dat.price);
  let comp;
  let maxCost;
  const sellPrice = parseFloat(dat.price);
  const ref = db.ref("user_data/"+dat.sellerId+"/components/"+dat.itemId);
  const ref2 = db.ref("marketplace/").push();
  //  to check if there is proper integeral value
  if (dat.quant<1) {
    return "Error: Fractional Quantity";
  }
  if (sellPrice<0) {
    return "Error: Negative Sale Price";
  }
  dat.quant = Math.floor(parseInt(dat.quant));
  return ref.once("value", (s)=>{
    comp = s.val();
    maxCost = parseFloat(comp.comp_maxCost)*parseFloat(dat.quant);
  }).then(()=>{
    comp.comp_quan=parseInt(comp.comp_quan)-parseInt(dat.quant);
    comp.price=parseInt(comp.price)-parseInt(dat.price);
    //  to limit sale price
    if (maxCost<sellPrice) {
      return "Error: Exceeds Circuit Limitations";
    }
    //  to check for quantity
    if (comp.comp_quan<0) {
      return "Error: Insufficient Quantity";
    }
    ref.set(comp).then(()=>{
      if (comp.comp_quan == 0) {
        ref.remove();
      }
      comp.comp_quan = dat.quant;
      const transactionKey = ref2.key;
      const transaction = {
        trans_id: transactionKey,
        price: dat.price,
        component: comp,
        reseller: dat.sellerId,
      };
      ref2.set(transaction).then(()=>{
        //  console.log("Completed");
        return "Sell Complete";
      }).catch((err)=>{
        console.log(err);
        return err;
      });
    }).catch((err)=>{
      console.log(err);
      return err;
    });
  }).catch((err)=>{
    console.log(err);
    return err;
  });
});

exports.buy = functions.https.onCall((data, context)=>{
  let toke = 1;
  const prodId = data.prodId;
  const custId = data.custId;
  const ref1 = "user_data/"+custId+"/components/";
  const trash = db.ref("marketplace/"+ prodId);
  let item;
  let buyer;
  let seller;
  return trash.once("value", (sn)=>{
    item = sn.val();
  }).then(()=> {
    db.ref("user_data/"+custId).once("value", (s)=>{
      buyer = s.val();
    }).then(()=> {
      db.ref("user_data/"+item.reseller).once("value", (s)=>{
        seller = s.val();
      }).then(()=> {
        if (custId!=item.reseller) {
          buyer.cash =parseInt(buyer.cash) - parseInt(item.price);
          seller.cash =parseInt(seller.cash) + parseInt(item.price);
          if (buyer.cash<0) {
            return "Error: Insufficient Funds";
          }
        }
        db.ref("user_data/"+item.reseller).set(seller).then(()=>{
          db.ref("user_data/"+custId).set(buyer).then(()=>{
            const ref2 = ref1 + item.component.comp_id;
            db.ref(ref1).once("value", (s)=>{
              s.forEach((cs)=>{
                if (cs.val().comp_id == item.component.comp_id) {
                  let addi = item.component.comp_quan;
                  let a = parseInt(addi) + parseInt(cs.val().comp_quan);
                  item.component.comp_quan = a;
                  addi = cs.val().price;
                  a = item.price;
                  const f = parseInt(addi) + parseInt(a);
                  item.component.price = f;
                  toke = 0;
                }
              });
            }).then(()=>{
              if (toke) {
                item.component.price = item.price;
              }
              db.ref(ref2).set(item.component).then(()=>{
                item.customer = custId;
                item.time = Date();
                db.ref("transactions/"+ prodId).set(item).then(()=>{
                  trash.remove().then(()=>{
                    //  console.log("Transaction Completed");
                    return "Transaction Completed";
                  }).catch((err)=>{
                    console.log(err);
                    return err;
                  });
                }).catch((err)=>{
                  console.log(err);
                  return err;
                });
              }).catch((err)=>{
                console.log(err);
                return err;
              });
            }).catch((err)=>{
              console.log(err);
              return err;
            });
          }).catch((err)=>{
            console.log(err);
            return err;
          });
        }).catch((err)=>{
          console.log(err);
          return err;
        });
      }).catch((err)=>{
        console.log(err);
        return err;
      });
    }).catch((err)=>{
      console.log(err);
      return err;
    });
  }).catch((err)=>{
    console.log(err);
    return err;
  });
});
*/
