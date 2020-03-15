#include <server.h>
#include <Authenticator.h>
#include <Database.h>

using namespace ucm;

int main(int argc, char** argv){

    CrowServer server(argc, argv);
    Database* database = new Database("misc/db.txt");
    Authenticator auth(database);

    server.renderHTML("/", "index.html");

    server.route("/login", [&](const request& req, response& res){
        if (req.has_params({"username", "password"})){

            std::string username = req.url_params.get("username");
            std::string password = req.url_params.get("password");

            ucm::json outcome = auth.authenticate(username, password);

            res.sendJSON(outcome);
            
        }
        else{
            res.sendError400();
        } 
    });

    server.route("/signup", [&](const request& req, response& res){
        if (req.has_params({"username", "password", "fname", "lname", "email"})){

            std::string username = req.url_params.get("username");
            std::string password = req.url_params.get("password");
            std::string firstName = req.url_params.get("fname");
            std::string lastName = req.url_params.get("lname");
            std::string email = req.url_params.get("email");

            ucm::json outcome = auth.signup(username, password, firstName, lastName, email);

            
            res.sendJSON(outcome);
            
        }
        else{
            res.sendError400();
        } 
    });

    server.route("/details", [&](const request& req, response& res){
        if (req.has_params({"username", "token"})){
            std::string username = req.url_params.get("username");
            std::string token = req.url_params.get("token");

            ucm::json response = auth.details(username, token);

            res.sendJSON(response);
        }
        else{
            res.sendError400();
        }
    });


    server.run();
}
