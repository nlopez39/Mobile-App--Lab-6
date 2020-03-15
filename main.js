var token = null;
var uid = null;

$(document).ready(function(){
	$("#userArea").hide();
	$("#signInBox").show();
	$("#usernameInput").focus();

	$("#signInButton").click(function(){
		var username = $("#usernameInput").val();
		var password = $("#passwordInput").val();
		uid = username;
		$.get("/login", {username: username, password: password}, function(response){
			var details = JSON.parse(response);
			if (details["success"]){
				token = details["token"];
				$.get("/details", {username: uid, token: token}, function(resp){
					var userDetails = JSON.parse(resp);
					if (userDetails["success"]){
						var firstName = userDetails["details"]["firstName"];
						var lastName = userDetails["details"]["lastName"];
						$("#signInBox").hide();
						$("#userHeading").html("Welcome " + firstName + " " + lastName);
						$("#userArea").show();
					}
				});
			}
			else {
				alert("Invalid username/password.");
				$("#usernameInput").val("");
				$("#passwordInput").val("");
				$("#usernameInput").focus();
			}
		})
	});

	$("#showSignupFormButton").click(function(){
		$("#signInBox").hide();
		$("#createAccountBox").show();
		$("#usernameSelection").focus();
	});

	$("#createAccountButton").click(function(){
		var usernameChoice = $("#usernameSelection").val();
		var passwordChoice = $("#passwordSelection").val();
		var firstName = $("#firstNameInput").val();
		var lastName = $("#lastNameInput").val();
		var email = $("#emailInput").val();

		$.get("/signup", {username: usernameChoice, password: passwordChoice, fname: firstName, lname: lastName, email: email}, function(response){
			var details = JSON.parse(response);
			if (details["success"]){
				alert("User account successfully created...");
				$("#createAccountBox").hide();
				$("#signInBox").show();
				$("#usernameInput").focus();
			}
			else{
				alert("Could not create account. " + details["message"]);
			}
		})
	});

	$("#cancelAccountCreationButton").click(function(){
		$("#usernameSelection").val("");
		$("#passwordSelection").val("");
		$("#firstNameInput").val("");
		$("#lastNameInput").val("");
		$("#emailInput").val("");
		$("#createAccountBox").hide();
		$("#signInBox").show();
		$("#usernameInput").focus();
	});
});
