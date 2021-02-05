document.getElementById("result-section").style.display = "none";
document.getElementById("about-section-result-header").style.display = "none";

let submitBtn = document.getElementById("submit-button");
let backBtn = document.getElementById("back-button");
submitBtn.addEventListener("click", () => {
  document.getElementById("about-section-main-header").style.display = "none";
  document.getElementById("about-section-result-header").style.display =
    "inline";
  document.getElementById("result-section").style.display = "flex";
  document.getElementById("application-field").style.display = "none";
  document.getElementById("image-ai").style.display = "none";
});

backBtn.addEventListener("click", () => {
  document.getElementById("about-section-main-header").style.display = "inline";
  document.getElementById("about-section-result-header").style.display = "none";
  document.getElementById("result-section").style.display = "none";
  document.getElementById("application-field").style.display = "flex";
  document.getElementById("image-ai").style.display = "flex";
});


