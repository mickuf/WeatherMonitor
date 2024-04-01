using System.Text.Json;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

var sensorArray = new List<Sensor>();

app.MapPost("/sensor", (Sensor value) =>
{
    sensorArray.Add(value);

    string json = JsonSerializer.Serialize(value);

    File.AppendAllText(@"path.json", $"{DateTime.Now}" + json + $",{Environment.NewLine}");

    return Results.Ok();
});

app.MapGet("/sensor", () =>
{
    return Results.Ok($"Readings number: {sensorArray?.Count} Last reading: {sensorArray?.Last()}");
});

app.Run();

public record Sensor(string BoardId, Inside Inside, Outside Outside);

public record Inside(float Temperature, int HumidityPercentage, float HeatIndex, int Pressure);

public record Outside(float Temperature, int HumidityPercentage, float HeatIndex, int LumosityPercentage);

